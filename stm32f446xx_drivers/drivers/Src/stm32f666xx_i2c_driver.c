/*
 * stm32f666xx_i2c_driver.c
 *
 *  Created on: Jan 1, 2024
 *      Author: Narendran Srinivasan
 *		E-mail: iamnarendrans@outlook.com
 */

#include "stm32f446xx_i2c_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};

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
	{
		SystemClk = 16000000;
	}else if (clksrc == 1)
	{
		SystemClk = 25000000;
	}else if (clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClk();
	}

	// For AHB Prescaler find
	temp = ((RCC->CFRG >> 10) & 0x7);

	if (temp < 8)
	{
		ahbp = 1;
	}else
	{
		ahbp = AHB_PreScaler[temp - 8];
	}

	// For APB Prescaler find
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
	tempreg |= (pI2CHandle->I2C_Config.I2C_AckCtrl << 10);
	pI2CHandle->pI2Cx->CR1 = tempreg;

	// Configure the FREQ field in CR2
	tempreg = 0;
	tempreg |= (RCC_GetPCLK1Value() / 1000000U);
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

	// Program the device own address
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddr << 1;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	// CCR Calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
	{
		// Mode is standard mode
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= (ccr_value & 0xFFF);
	}else
	{
		// Mode is Fast mode
		tempreg |= (1 << 15);
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}else
		{
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}

		tempreg |= (ccr_value & 0xFFF);

	}
	pI2CHandle->pI2Cx->CCR = tempreg;

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
//uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
//{
//	if(pI2Cx->SR & FlagName)
//	{
//		return FLAG_SET;
//	}
//	return FLAG_RESET;
//}
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
