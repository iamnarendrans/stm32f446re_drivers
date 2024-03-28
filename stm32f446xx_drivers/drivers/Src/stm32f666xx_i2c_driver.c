/*
 * stm32f666xx_i2c_driver.c
 *
 *  Created on: Jan 1, 2024
 *      Author: Narendran Srinivasan
 *		E-mail: iamnarendrans@outlook.com
 */

#include "stm32f446xx_i2c_driver.h"

/****************************************************************************************************************
 * 													PRIVATE VARIABLES
 ****************************************************************************************************************/
uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};
/****************************************************************************************************************/

/****************************************************************************************************************
 * 											PRIVATE FUNCTIONS DEFINITION
 ****************************************************************************************************************/
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t ReadOrWrite);
static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);
static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *pI2CHandle);
static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pI2CHandle);
/*****************************************************************************************************************/

/******************************************************************************************************************
 * 													FUNCTIONS
 ****************************************************************************************************************/

/******************************************************************************************************************
 * @fn									- RCC_GetPLLOutputClk
 *
 * @brief								- This function returns the PLL clock value
 *
 * @param[None]							- None
 *
 * @return								- PLL clock value
 *
 * @note								- None
 *****************************************************************************************************************/
uint32_t RCC_GetPLLOutputClk(void)
{
	// will implement in future

	return 0;
}

/******************************************************************************************************************
 * @fn									- RCC_GetPCLK1Value
 *
 * @brief								- This function returns the peripheral 1 clock value
 *
 * @param[None]							- None
 *
 * @return								- APB1 clock value
 *
 * @note								- None
 *****************************************************************************************************************/
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1, SystemClk;

	uint8_t clksrc, temp, ahbp,apb1p;

	clksrc = ((RCC->CFRG >> 2) & 0x3);

	if (clksrc == 0)
	{	// If clksrc = 0 => which is HSI
		SystemClk = 16000000;
	}else if (clksrc == 1)
	{	// If clksrc = 1 => which is HSE
		SystemClk = 25000000;
	}else if (clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClk();
	}

	// For AHB Prescaler find
	temp = ((RCC->CFRG >> 4) & 0xF);

	if (temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}

	// For APB1 Prescaler find
	temp = ((RCC->CFRG >> 10) & 0x7);

	if (temp < 4)
	{
		apb1p = 1;
	}else
	{
		apb1p = APB1_PreScaler[temp - 4];
	}

	pclk1 = (SystemClk/ahbp) / apb1p;

	return pclk1;
}

/********************************************Peripheral Clock Control**********************************************/
/******************************************************************************************************************
 * @fn									- I2C_PeriClockControl
 *
 * @brief								- This function enables or disables peripheral clock for the given I2Cx bus
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t EnorDi]				- Enabling/Disabling Clock of the peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();
		}else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_DI();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/
/******************************************************************************************************************
 * @fn									- I2C_Init
 *
 * @brief								- This function will Initalize the I2Cx Peripheral
 *
 * @param[I2C_Handle_t *pI2CHandle]		- Pointer to the Handle structure
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	// Configure the I2C_CR1
	uint32_t tempreg = 0;

	// Acknowledge control bit
	tempreg |= (pI2CHandle->I2C_Config.I2C_AckCtrl << I2C_CR1_ACK);
	pI2CHandle->pI2Cx->CR1 = tempreg;

	// Configure the FREQ field in CR2
	tempreg = 0;
	tempreg |= (RCC_GetPCLK1Value() / 1000000U);
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

	// Program the device own address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddr << I2C_OAR1_ADD71;
	tempreg |= (1 << 14); //Mandatory from RM
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	// CCR Calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// Mode is standard mode, calculation is below
		/*
		 * if Thigh = Tlow in SCL, then
		 * Tscl = 2 * CCR * Tpclk1
		 * CCR = Tscl / 2 * Tpclk1
		 * CCR = Fpclk1 / 2 * Fscl
		 */
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= (ccr_value & 0xFFF);
	}else
	{
		// Mode is Fast mode, calculation is below
		tempreg |= (1 << I2C_CCR_F_S);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY);

		/*
		 * if Tlow = 2 * Thigh, then Duty = 0
		 * if Tlow = 1.7 * Thigh, then Duty = 1
		 */

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			/*
			 * Duty = 0
			 * CCR = Fpclk1 / 3 * Fscl
			 */
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}else
		{
			/*
			 * Duty = 1
			 * CCR = Fpclk1 / 25 * Fscl
			 */
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}

		tempreg |= (ccr_value & 0xFFF);

	}
	pI2CHandle->pI2Cx->CCR = tempreg;

	// Trise Configuration
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// Standard mode
		tempreg = (RCC_GetPCLK1Value() / 1000000U) + 1;
	}
	else
	{
		// Fast mode
		tempreg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
		pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);

	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_DeInit
 *
 * @brief								- This function will DeInitalize the I2Cx Peripheral
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();
	}
	else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();
	}else if(pI2Cx == I2C3)
	{
		I2C3_REG_RESET();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**********************************************Data Send/Receive APIs**********************************************/
/******************************************************************************************************************
 * @fn									- I2C_MasterSendData
 *
 * @brief								- This function is used to send the data over I2C as master
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t *pTxBuffer]			- Transmit buffer holds the data to be sent
 * @param[uint8_t Len]					- length of the buffer
 * @param[uint8_t SlaveAddr]			- slave address / device address
 *
 * @return								- None
 *
 * @note								- Blocking Method
 *****************************************************************************************************************/
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	// 1. Generate the start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	// 2. Confirm that start generation is completed by checking the SB flag in SR1
	// Note*: Until the SB is cleared SCL will be streched (pulled to LOW)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	// 3. Send the address to the slave with r/nw bit set to w(0) (total 8 bits)
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, SlaveAddr, I2C_WRITE);

	// 4. Confirm the address  phase is completed by checking the ADDR flag in the SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

	// 5. Clear the ADDR flag according to its software sequence
	// Note*: Until ADDR is cleared SCL will be streched (pulled to LOW)
	I2C_ClearADDRFlag(pI2CHandle);

	// 6. Send the data until Len becomes 0
	while(Len > 0)
	{
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));  // Wait until the TXE is set
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	// 7. When Len becomes zero wait for TXE = 1 and BTF = 1 before generating a stop condition
	// Note*: TXE = 1, BTF = 1, means that both SR and DR are empty and next transmission should begin
	// When BTF = 1 SCL will be stretched (pulled to LOW)

	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE));

	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

	// 8. Generate the stop condition and master need not wait for the completion of stop condition
	// Note*: generating STOP, automatically clears BTF
	if(Sr == I2C_DISABLE_SR)
	{
		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_MasterReceiveData
 *
 * @brief								- This function is used to receive the data over I2C as master
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t *pRxBuffer]			- receive buffer holds the data to be sent
 * @param[uint8_t Len]					- length of the buffer
 * @param[uint8_t SlaveAddr]			- slave address / device address
 *
 * @return								- None
 *
 * @note								- Blocking Method
 *****************************************************************************************************************/
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	// 1. Generate START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	// 2. Confirm that start condition is completed by checking the SB flag in the SR1
	// Note*: Until SB is cleared SCL will be streched (pulled to LOW)
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB));

	// 3. Send the address of the slave with r/w bit set to R(1) - (Total 8 bits)
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, SlaveAddr, I2C_READ);

	// 4. wait until address phase is completed by checking the ADDR flag in the SR1
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));

	// Procedure to read only 1 byte from the slave
	if(Len == 1)
	{
		// Disable Acking
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DI);

		// clear the ADDR flag
		I2C_ClearADDRFlag(pI2CHandle);

		// wait until RXNE becomes 1
		while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

		// Generate the stop condition
		if(Sr == I2C_DISABLE_SR)
		{
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		}

		// read data into the buffer
		*pRxBuffer = pI2CHandle->pI2Cx->DR;

	}

	// Procedure to read data from slave when Len > 1
	if(Len > 1)
	{
		// Clear the ADDR Flag
		I2C_ClearADDRFlag(pI2CHandle);

		// Read data until the len becomes zero
		for(uint32_t i = Len; i > 0; i--)
		{
			// Wait until RXNE becomes 1
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE));

			if(i == 2) // if the last 2 bytes are remaining
			{
				// Disable Acking
				I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DI);

				// Generate the stop condition
				if(Sr == I2C_DISABLE_SR)
				{
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
				}

			}

			// read data from data register into the buffer
			*pRxBuffer = pI2CHandle->pI2Cx->DR;

			// increment the data buffer address
			pRxBuffer++;
		}
	}

	// re-enable ACKing
	if(pI2CHandle->I2C_Config.I2C_AckCtrl == I2C_ACK_EN)
	{
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_EN);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_MasterSendDataIT
 *
 * @brief								- This function is used to send the data over I2C as master
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t *pTxBuffer]			- Transmit buffer holds the data to be sent
 * @param[uint8_t Len]					- length of the buffer
 * @param[uint8_t SlaveAddr]			- slave address / device address
 *
 * @return								- None
 *
 * @note								- Non-Blocking Method
 *****************************************************************************************************************/
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	uint8_t busyState = pI2CHandle->TxRxState;

	if( (busyState != I2C_BUSY_IN_TX) && (busyState != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVTEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);

	}

	return busyState;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_MasterReceiveDataIT
 *
 * @brief								- This function is used to receive the data over I2C as master
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t *pRxBuffer]			- receive buffer holds the data to be sent
 * @param[uint8_t Len]					- length of the buffer
 * @param[uint8_t SlaveAddr]			- slave address / device address
 *
 * @return								- None
 *
 * @note								- Non-Blocking Method
 *****************************************************************************************************************/
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr)
{
	uint8_t busyState = pI2CHandle->TxRxState;

	if((busyState != I2C_BUSY_IN_TX) && (busyState != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = Len;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVTEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_ITERREN);

	}

	return busyState;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************IRQ Configuration and ISR Handler*************************************/
/******************************************************************************************************************
 * @fn									- I2C_IRQInterruptConfig
 *
 * @brief								- This function will config the Interrupt IRQ Number
 *
 * @param[uint8_t IRQNumber]			- Interrupt handler number
 * @param[uint8_t IRQPriority]			- Priority of the interrupt execution
 * @param[uint8_t EnorDi]				- Enabling/Disabling Clock of the peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31)
		{
			// Program ISER Register (bewteen 0 - 31)
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber >= 31 && IRQNumber < 64)
		{
			// Program ISER1 Register (bewteen 32 - 63)
			 * NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// Program ISER2 Register (bewteen 64 - 95)
			 * NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if(IRQNumber <= 31)
		{
			// Program ICER Register (bewteen 0 - 31)
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber >= 31 && IRQNumber < 64)
		{
			// Program ICER1 Register (bewteen 32 - 63)
			 * NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			// Program ISER2 Register (bewteen 64 - 95)
			 * NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_IRQPriorityConfig
 *
 * @brief								- This function will configure the IRQ/Interrupt Priority Number
 *
 * @param[uint8_t IRQNumber]			- IRQ Number from the NVIC table
 * @param[uint32_t IRQPriority]			- Interrupt priority from the NVIC table
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. First lets findout the IPR Register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift_amount);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_EV_IRQHandling
 *
 * @brief								- This function is used to handle I2Cx interrupts triggred by Events
 *
 * @param[I2C_Handle_t *pI2CHandle]		- I2C Handle Structure
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	// Interrupt handling for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;

	temp1 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITEVTEN);
	temp2 = pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITBUFEN);

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_SB);
/***********************Check for start bit event handling************************************/
	// 1. Handle for an event generated by SB event
	// Note*: Start bit flag is only applicant in master mode
	if(temp1 && temp3)
	{
		// The interrupt is generated because of SB event
		// This block will not be executed in slave mode, because for slave SB is always zero
		// In this block lets executed the address phase
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_WRITE);
		}
		else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_READ);
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_ADDR);
/***********************Check for Address bit event handling************************************/
	// 2. Handle for interrupt generated by ADDR Event
	// Note*: When master mode - Address is sent
	// 		  When slave mode  - Address matched with own address
	if(temp1 && temp3)
	{
		// The interrupt is generated because of ADDR event flag
		I2C_ClearADDRFlag(pI2CHandle);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_BTF);
/***********************Check for Byte transfer finished event handling************************************/
	// 3. Handle for interrupt generated by BTF(Byte transfer finished) event
	if(temp1 && temp3)
	{
		// The interrupt is generated because of BTF Event [Byte transfer finished]
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
		{
			// Make sure that TXE is also set
			if(pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TxE))
			{
				// BTF, TXE = 1
				if(pI2CHandle->TxLen == 0)
				{
					// 1. Generate the stop condition
					if(pI2CHandle->Sr == I2C_DISABLE_SR)
					{
						I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
					}

					// 2. Reset all the member elements of the handle structure
					I2C_CloseSendData(pI2CHandle);

					// 3. Notify the application about transmission complete
					I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_TX_CMPLT);
				}
			}
		}
		else if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			;
		}

	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_STOPF);
/***********************Check for STOPF bit event handling************************************/
	// 4. Handle for interrupt generated by STOPF event
	// Note*: stop detection flag is only applicable in slave mode. For master this flag will
	if(temp1 && temp3)
	{
		// STOPF flag is set
		// Clear the STOPF (i.e 1) Read SR1 & Write to CR1
		pI2CHandle->pI2Cx->CR1 |= 0x0000;

		// Notify the application that STOP is detected
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_STOP);
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_TxE);
/***********************Check for Transmit bit event handling************************************/
	// 5. Handle for interrupt generated by TXE event
	if(temp1 && temp2 && temp3)
	{
		// Check for device mode, if master only do the below logic
		if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
		{
			// TXE flag is set
			// We have to do the data transmission
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_TX)
			{
				I2C_MasterHandleTXEInterrupt(pI2CHandle);
			}
		}
	}

	temp3 = pI2CHandle->pI2Cx->SR1 & (1 << I2C_SR1_RxNE);
/***********************Check for Receive bit event handling************************************/
	if(temp1 && temp2 && temp3)
	{
		if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
		{
			// The device is master
			// RXNE flag is set
			if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
			{
				I2C_MasterHandleRXNEInterrupt(pI2CHandle);
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_ERR_IRQHandling
 *
 * @brief								- This function is used to handle I2Cx interrupts triggred by Errors
 *
 * @param[I2C_Handle_t *pI2CHandle]		- I2C Handle Structure
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_ERR_IRQHandling(I2C_Handle_t *pI2CHandle)
{

	uint32_t temp1,temp2;

    //Know the status of  ITERREN control bit in the CR2
	temp2 = (pI2CHandle->pI2Cx->CR2) & ( 1 << I2C_CR2_ITERREN);


/***********************Check for Bus error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1<< I2C_SR1_BERR);
	if(temp1  && temp2 )
	{
		//This is Bus error

		//Implement the code to clear the buss error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_BERR);

		//Implement the code to notify the application about the error
	   I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_BERR);
	}

/***********************Check for arbitration lost error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_ARLO );
	if(temp1  && temp2)
	{
		//This is arbitration lost error

		//Implement the code to clear the arbitration lost error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_ARLO);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_ARLO);

	}

/***********************Check for ACK failure  error************************************/

	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_AF);
	if(temp1  && temp2)
	{
		//This is ACK failure error

	    //Implement the code to clear the ACK failure error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_AF);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_AF);
	}

/***********************Check for Overrun/underrun error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_OVR);
	if(temp1  && temp2)
	{
		//This is Overrun/underrun

	    //Implement the code to clear the Overrun/underrun error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_OVR);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_OVR);
	}

/***********************Check for Time out error************************************/
	temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_TIMEOUT);
	if(temp1  && temp2)
	{
		//This is Time out error

	    //Implement the code to clear the Time out error flag
		pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_TIMEOUT);

		//Implement the code to notify the application about the error
		I2C_ApplicationEventCallback(pI2CHandle,I2C_ERROR_TIMEOUT);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************Other Peripheral Control APIs**************************************/
/******************************************************************************************************************
 * @fn									- I2C_PeripheralControl
 *
 * @brief								- This function will enable the I2C peripheral
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base address of the I2Cx (x: 1, 2) peripheral
 * @param[uint8_t EnOrDi]				- Enable/Disable the I2C peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}
	else
	{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_GetFlagStatus
 *
 * @brief								- This function will give the status of the flag
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint32_t FlagName]			- Name of the Flag
 *
 * @return								- status of the flag either 0 or 1
 *
 * @note								- None
 *****************************************************************************************************************/
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_MasterHandleTXEInterrupt
 *
 * @brief								- This function handle the TXE Event Interrupt
 *
 * @param[I2C_Handle_t *pI2CHandle]		- Handle structure of I2C peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void I2C_MasterHandleTXEInterrupt(I2C_Handle_t *pI2CHandle)
{
	if(pI2CHandle->TxLen > 0)
	{
		// 1. Load the data into DR
		pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);

		// 2. Decrement the TxLen
		pI2CHandle->TxLen--;

		// 3. Increment the buffer address
		pI2CHandle->pTxBuffer++;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_MasterHandleRXNEInterrupt
 *
 * @brief								- This function handle the RXNE Event Interrupt
 *
 * @param[I2C_Handle_t *pI2CHandle]		- Handle structure of I2C peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void I2C_MasterHandleRXNEInterrupt(I2C_Handle_t *pI2CHandle)
{
	// We have to do the data reception
	if(pI2CHandle->RxSize == 1)
	{
		*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;

		pI2CHandle->RxLen--;
	}

	if(pI2CHandle->RxSize > 1)
	{
		if(pI2CHandle->RxLen == 2)
		{
			// clear the ACK bit
			I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);
		}

		*pI2CHandle->pRxBuffer = pI2CHandle->pI2Cx->DR;
		pI2CHandle->pRxBuffer++;
		pI2CHandle->RxLen--;
	}

	if(pI2CHandle->RxLen == 0)
	{
		// Close the I2C data reception and notify the application

		// 1. Generatet the stop condition
		if(pI2CHandle->Sr == I2C_DISABLE_SR)
		{
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		}

		// 2. Close the I2C Rx
		I2C_CloseReceiveData(pI2CHandle);

		// 3. Notify the application
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_RX_CMPLT);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_ApplicationEventCallback
 *
 * @brief								- This function is an application event callback from application layer
 *
 * @param[I2C_Handle_t *pI2CHandle]		- I2C peripheral Handler
 * @param[uint8_t AppEvent]				- Event to be passed
 * @return								- None
 *
 * @note								- Implemented as week function, if user not use this in application code
 *****************************************************************************************************************/
__weak void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent)
{
	// This is a weak implementation. the application may override this function
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/********************************************Private Funtions and callbacks ***************************************/
/******************************************************************************************************************/

/******************************************************************************************************************
 * @fn									- I2C_GenerateStartCondition
 *
 * @brief								- This function is used to generate the start conditon of I2C bus
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_ExecuteAddressPhase
 *
 * @brief								- This function is used to execute the slave address the Data register
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t SlaveAddr]			- User give slave address
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t ReadOrWrite)
{
	if(ReadOrWrite == I2C_WRITE)
	{
		SlaveAddr = SlaveAddr << 1;
		SlaveAddr &= ~(1);			// SlaveAddr is slave address + r/w(0) bit=0
		pI2Cx->DR = SlaveAddr;
	}
	else if(ReadOrWrite == I2C_READ)
	{
		SlaveAddr = SlaveAddr << 1;
		SlaveAddr |= ~(1);			// SlaveAddr is slave address + r/w(1) bit=1
		pI2Cx->DR = SlaveAddr;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_ClearADDRFlag
 *
 * @brief								- This function is used to clear the address flag
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
	uint32_t dummy_read;
	// Check for device mode
	if(pI2CHandle->pI2Cx->SR2 & (1 << I2C_SR2_MSL))
	{
		// Device is in master mode
		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
		{
			if(pI2CHandle->RxSize == 1)
			{
				// First Disable the ack
				I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);

				// clear the ADDR flag (Read SR1, Read SR2)
				dummy_read = pI2CHandle->pI2Cx->SR1;
				dummy_read = pI2CHandle->pI2Cx->SR2;
				(void)dummy_read;
			}
		}
		else
		{
			// clear the ADDR flag (Read SR1, Read SR2)
			dummy_read = pI2CHandle->pI2Cx->SR1;
			dummy_read = pI2CHandle->pI2Cx->SR2;
			(void)dummy_read;
		}
	}else
	{
		// Devie is in slave mode
		// clear the ADDR flag (Read SR1, Read SR2)
		dummy_read = pI2CHandle->pI2Cx->SR1;
		dummy_read = pI2CHandle->pI2Cx->SR2;
		(void)dummy_read;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_GenerateStopCondition
 *
 * @brief								- This function is used to generate the stop conditon of I2C bus
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_ManageAcking
 *
 * @brief								- This function is used to manage/handle ACK/NACK
 *
 * @param[I2C_RegDef_t *pI2Cx]			- Base Address of the I2Cx Peripheral
 * @param[uint8_t EnorDi]				- Enable/Disbale Input for ACK Enable & Disable
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == I2C_ACK_EN)
	{
		// Enable Acknowledgement
		pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	}
	else
	{
		// Disable Acknowledgement
		pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_CloseSendData
 *
 * @brief								- This function will close the I2C Transmission in interrupt mode
 *
 * @param[I2C_Handle_t *pI2CHandle]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle)
{
	// Implement the code to disable the ITBUFEN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);

	// Implement the code to diable the ITEVTFN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->pTxBuffer = NULL;
	pI2CHandle->TxLen = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- I2C_CloseReceiveData
 *
 * @brief								- This function will close the I2C reception in interrupt mode
 *
 * @param[I2C_Handle_t *pI2CHandle]			- Base Address of the I2Cx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle)
{
	// Implement the code to disable the ITBUFEN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);

	// Implement the code to diable the ITEVTFN Control bit
	pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);

	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->pRxBuffer = NULL;
	pI2CHandle->RxLen = 0;
	pI2CHandle->RxSize = 0;

	if(pI2CHandle->I2C_Config.I2C_AckCtrl == I2C_ACK_EN)
	{
		I2C_ManageAcking(pI2CHandle->pI2Cx, ENABLE);
	}


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
