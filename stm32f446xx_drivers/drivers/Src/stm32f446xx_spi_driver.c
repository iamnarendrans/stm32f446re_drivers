/*
 * stm32f446xx_spi_driver.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Narendran Srinivasan
 */


#include "stm32f446xx_spi_driver.h"

static void spi_txne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);

/********************************************Peripheral Clock Control**********************************************/
/******************************************************************************************************************
 * @fn									- SPI_PeriClockControl
 *
 * @brief								- This function enables or disables peripheral clock for the given SPIx bus
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base Address of the SPIx Peripheral
 * @param[uint8_t EnorDi]				- Enabling/Disabling Clock of the peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}else if(pSPIx == SPI4)
		{
			SPI4_PCLK_EN();
		}
	}else
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/
/******************************************************************************************************************
 * @fn									- SPI_Init
 *
 * @brief								- This function will Initalize the SPIx Peripheral
 *
 * @param[SPI_Handle_t *pSPIHandle]		- Pointer to the Handle structure
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// Configure the SPI_CR1 Register

	// Enable the peripheral clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	uint32_t tempReg = 0;

	// 1. Configure the device mode
	tempReg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDI mode should be cleared
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDI mode should be set
		tempReg |= (1 << SPI_CR1_BIDIMODE);
	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// BIDI mode should be cleared & RXONLY bit must be set
		tempReg &= ~(1 << SPI_CR1_BIDIMODE);
		tempReg |= (1 << SPI_CR1_RXONLY);
	}

	// 3. Configure the SPI serial clock speed (baudRate)
	tempReg |= pSPIHandle->SPIConfig.SPI_ClkSpeed << SPI_CR1_BR;

	// 4. Configure the DFF [DATA FRAME FORMAT]
	tempReg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	// 5. Configure the CPOL
	tempReg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	// 6. Configure the CPHA
	tempReg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	// 7. Configur the SSM
	tempReg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempReg;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_DeInit
 *
 * @brief								- This function will DeInitalize the SPIx Peripheral
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base Address of the SPIx Peripheral
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
	{
		SPI1_REG_RESET();
	}
	else if(pSPIx == SPI2)
	{
		SPI2_REG_RESET();
	}else if(pSPIx == SPI3)
	{
		SPI3_REG_RESET();
	}else if(pSPIx == SPI4)
	{
		SPI4_REG_RESET();
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_GetFlagStatus
 *
 * @brief								- This function will give the status of the flag
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base Address of the SPIx Peripheral
 * @param[uint32_t FlagName]			- Name of the Flag
 *
 * @return								- status of the flag either 0 or 1
 *
 * @note								- None
 *****************************************************************************************************************/
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************Data Send/Receive APIs**********************************************/
/******************************************************************************************************************
 * @fn									- SPI_SendData
 *
 * @brief								- This function will Send Data into Master/Slave
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base Address of the SPIx Peripheral
 * @param[uint8_t *pTxBuffer]			- Transmit buffer pointer to address the Tx butter
 * @param[uint32_t Len]					- length of the TxBuffer
 *
 * @return								- None
 *
 * @note								- This is a blocking call / Polling type
 *****************************************************************************************************************/
bool SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	bool status = false;

	while(Len > 0)
	{
		// 1. Wait until TXE is set
		//while(!(pSPIx->SR & (1 << 1)));
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// 2. Check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			// 1. Load the data into the DR
			pSPIx->DR = *(uint16_t*)pTxBuffer;
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			// 8 bit DFF
			pSPIx->DR = *(uint8_t*)pTxBuffer;
			Len--;
			pTxBuffer++;

		}
	}

	if(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) != H_OK || SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) != 0)
	{
		status = true;
	}

	return status;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_ReceiveData
 *
 * @brief								- This function will receive Data from Master/Slave
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base Address of the SPIx Peripheral
 * @param[uint8_t *pRxBuffer]			- Receive buffer pointer to address the Rx butter
 * @param[uint32_t Len]					- length of the RxBuffer
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// 1. Wait until RXNE is set
		//while(!(pSPIx->SR & (1 << 1)));
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		// 2. Check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			// 1. Load the data from DR to Rx buffer address
			*(uint16_t*)pRxBuffer = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}else
		{
			// 8 bit DFF
			*(pRxBuffer) = pSPIx->DR;
			Len--;
			pRxBuffer++;

		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************IRQ Configuration and ISR Handler*************************************/
/******************************************************************************************************************
 * @fn									- SPI_IRQInterruptConfig
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
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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
 * @fn									- SPI_IRQPriorityConfig
 *
 * @brief								- This function will configure the IRQ/Interrupt Priority Number
 *
 * @param[uint8_t IRQNumber]			- IRQ Number from the NVIC table
 * @param[uint32_t IRQPriority]			- Interrupt priority from the NVIC table
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//1. First lets findout the IPR Register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift_amount);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_IRQHandling
 *
 * @brief								- This function will handle the IQR/ISR Interrupts
 *
 * @param[SPI_Handle_t *pHandle]		- SPI IRQHandling Struct
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	uint8_t temp1, temp2;
	// First lets check for TXE
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_TXE);
	temp2 = pHandle->pSPIx->SR & (1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		// Handle TXE
		spi_txne_interrupt_handle(pHandle);
	}

	// Check for RXNE
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE);
	temp2 = pHandle->pSPIx->SR & (1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		// Handle TXE
		spi_rxne_interrupt_handle(pHandle);
	}

	// check for ovr flag
	temp1 = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	temp2 = pHandle->pSPIx->SR & (1 << SPI_CR2_ERRIE);

	if(temp1 && temp2)
	{
		// Handle TXE
		spi_ovr_err_interrupt_handle(pHandle);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_PeripheralControl
 *
 * @brief								- This function will enable the SPI peripheral
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base address of the SPIx (x: 1, 2) peripheral
 * @param[uint8_t EnOrDi]				- Enable/Disable the SPI peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_SSIConfig
 *
 * @brief								- This function will Enable/Disable the SSI
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base address of the SPIx (x: 1, 2) peripheral
 * @param[uint8_t EnOrDi]				- Enable/Disable the SPI peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}
	else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_SSOEConfig
 *
 * @brief								- This function will alternatively make NSS high & low corresponding to
 * 										  SPE bit [SPI peripheral enable control bit]
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base address of the SPIx (x: 1, 2) peripheral
 * @param[uint8_t EnOrDi]				- Enable/Disable the SPI peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_SendDataIT
 *
 * @brief								- This function will just transmit from Tx buffer data
 *
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral handler structure
 * @param[uint8_t *pTxBuffer]			- Tx Buffer to store the received data
 * @param[uint32_t Len]					- length of the data
 * @return								- None
 *
 * @note								- Interrupt / Non blocking mode
 *****************************************************************************************************************/
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->TxState;
	if(state != SPI_BUSY_IN_TX)
	{
		// 1. Save the Tx buffer address and Len information in some global variables
		pSPIHandle -> pTxBuffer = pTxBuffer;
		pSPIHandle -> TxLen = Len;

		// 2. Mark the SPI state as busy in transmission so that
		// no other code take over same SPI peripheral until transmission is over
		pSPIHandle -> TxState = SPI_BUSY_IN_TX;

		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle -> pSPIx -> CR2 |= (1 << SPI_CR2_TXEIE);

		// 4. Data transmission will be handled by the ISR code (will implemented above)
	}

	return state;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_ReceiveDataIT
 *
 * @brief								- This function will just receive the Rx buffer data
 *
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral handler structure
 * @param[uint8_t *pRxBuffer]			- Rx Buffer to store the received data
 * @param[uint32_t Len]					- length of the data
 * @return								- None
 *
 * @note								- Interrupt / Non blocking mode
 *****************************************************************************************************************/
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;
	if(state != SPI_BUSY_IN_RX)
	{
		// 1. Save the Tx buffer address and Len information in some global variables
		pSPIHandle -> pRxBuffer = pRxBuffer;
		pSPIHandle -> RxLen = Len;

		// 2. Mark the SPI state as busy in transmission so that
		// no other code take over same SPI peripheral until transmission is over
		pSPIHandle -> RxState = SPI_BUSY_IN_TX;

		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle -> pSPIx -> CR2 |= (1 << SPI_CR2_RXNEIE);

		// 4. Data transmission will be handled by the ISR code (will implemented above)
	}

	return state;
}

/******************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************************************************
 * 										Some Helper functions implementations
 ******************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- spi_txne_interrupt_handle
 *
 * @brief								- This function will give transmit error for interrupt handler
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void spi_txne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	// 1. Check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
	{
		// 16 bit DFF
		// 1. Load the data into the DR
		pSPIHandle->pSPIx->DR = *(uint16_t*)pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}else
	{
		// 8 bit DFF
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;

	}

	if(!pSPIHandle->TxLen)
	{
		// TxLen is zero, so close the spi communication and inform the application that
		// Tx is over.
		// This prevents interrupts from setting up of TXE flag
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- spi_rxne_interrupt_handle
 *
 * @brief								- This function will give an receive error or for interrupt handler
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	// 1. Check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
	{
		// 16 bit DFF
		// 1. Load the data into the DR
		*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen -= 2;
		pSPIHandle->pRxBuffer--;
		pSPIHandle->pRxBuffer--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}else
	{
		// 8 bit DFF
		*(pSPIHandle->pRxBuffer) = (uint8_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer--;

	}

	if(!pSPIHandle->RxLen)
	{
		// Reception is complete
		// Lets turn off the RXNEIE interrupt
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- spi_ovr_err_interrupt_handle
 *
 * @brief								- This function will give an over run error for interrupt handler
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	// 1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->SR;

	}

	(void)temp;
	// 2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_CloseTransmission
 *
 * @brief								- This function will close the Transmission of the peripheral
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_CloseReception
 *
 * @brief								- This function will close the reception of the peripheral
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_ClearOVRFlag
 *
 * @brief								- This function is used to clear the overRun flag, if rxbuffer is overRun
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base address of the SPIx (x: 1, 2) peripheral
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_ApplicationEventCallback
 *
 * @brief								- This function is an application event callback from application layer
 *
 * @param[SPI_Handle_t *pSPIHandle]		- SPI peripheral Handler
 * @param[uint8_t AppEvent]				- Event to be passed
 * @return								- None
 *
 * @note								- Implemented as week function, if user not use this in application code
 *****************************************************************************************************************/
__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{
	// This is a weak implementation. the application may override this function
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- SPI_TransmitReceive
 *
 * @brief								- This function is used to transmit and receive data of each byte
 *
 * @param[SPI_RegDef_t *pSPIx]			- Base address of the SPIx (x: 1, 2) peripheral
 * @param[uint8_t tx_data]				- Data to be transmitted over MOSI
 * @return								- receivedData
 *
 * @note								- Polling Method
 *****************************************************************************************************************/
bool SPI_TransmitReceive(SPI_RegDef_t *pSPIx, uint8_t *tx_data, uint8_t *rx_data, uint8_t len)
{
	bool status = true;
	// Enable SPI
	// pSPIx->CR1 |= (1 << SPI_CR1_SPE);

    for (uint32_t i = 0; i < (len); ++i) {
        // Write Data to the register
        pSPIx->DR = tx_data[i];

        // Delay to ensure the SPI transaction completes (adjust as needed)
        // for(uint32_t j = 0; j < 100; j++);

        // Wait until SPI is not busy and Rx Buffer is not empty
        while (((pSPIx->SR) & (1 << SPI_SR_BSY)) || (!((pSPIx->SR) & (1 << SPI_SR_RXNE))));

        // Read a Byte from The Rx Buffer
        rx_data[i] = (uint8_t)pSPIx->DR;

        // Delay to ensure the SPI transaction completes (adjust as needed)
        // for(uint32_t j = 0; j < 100; j++);
    }

    if(SPI_GetFlagStatus(pSPIx, SPI_BUSY_FLAG) == 1)
    {
    	status = false;
    }

	return status;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
