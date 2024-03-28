/*
 * stm32f446xx_spi_driver.h
 *
 *  Created on: Dec 8, 2023
 *      Author: Narendran Srinivasan
 */

#ifndef INC_STM32F446XX_SPI_DRIVER_H_
#define INC_STM32F446XX_SPI_DRIVER_H_

#include "stm32f446xx.h"				/*! System Driver header inclusion*/

/*
 * Configuration structure for SPIz peripheral
 */

typedef struct
{
	uint8_t SPI_DeviceMode;			/*! Mode of the device [master or slave]*/
	uint8_t SPI_BusConfig;			/*! FullDuplex, HalfDuplex configuration*/
	uint8_t SPI_ClkSpeed;			/*! Clock Speed configuration */
	uint8_t SPI_DFF;				/*! Data Frame format [8bit or 16bit]*/
	uint8_t SPI_CPOL;				/*! Clock polarity */
	uint8_t SPI_CPHA;				/*! Clock phase */
	uint8_t SPI_SSM;				/*! Slave management [hardware or software]*/

}SPI_Config_t;


/*
 * Handle Structure for SPIx peripheral
 */

typedef struct
{
	SPI_RegDef_t	*pSPIx; 		/*! This holds the base address of the SPIx(x:0,1,2) peripheral */
	SPI_Config_t	SPIConfig;
	uint8_t			*pTxBuffer;		/*! To store the App. Tx Buffer address */
	uint8_t			*pRxBuffer;		/*! To store the App. Rx Buffer address */
	uint32_t		TxLen;			/*! To store Tx Len */
	uint32_t		RxLen;			/*! To store Rx Len */
	uint8_t			TxState;		/*! To store Tx State */
	uint8_t			RxState;		/*! To store Rx State */
}SPI_Handle_t;

/*
 * SPI Application states
 */
#define SPI_READY				0	/*! SPI bus is ready to Tx/Rx */
#define SPI_BUSY_IN_RX			1	/*! SPI bus is busy in RX mode */
#define SPI_BUSY_IN_TX			2	/*! SPI bus is busy in TX mode */

/*
 * Possible SPI Application events
 */

#define SPI_EVENT_TX_CMPLT		1	/*! SPI bus is completedTX event */
#define SPI_EVENT_RX_CMPLT		2	/*! SPI bus is completedRX event */
#define SPI_EVENT_OVR_ERR		3	/*! SPI bus is Over Run Error event */
#define SPI_EVENT_CRC_ERR		4	/*! SPI bus is CRC Error event */

/*
 * @SPI_DeviceMode
 */

#define SPI_DEVICE_MODE_MASTER				1	/*! SPI peripheral will act as master */
#define SPI_DEVICE_MODE_SLAVE				0	/*! SPI peripheral will act as slave */

/*
 * @SPI_BusConfig
 */

#define SPI_BUS_CONFIG_FD					1	/*!SPIx Bus configuration in FULLDUPLEX */
#define SPI_BUS_CONFIG_HD					2	/*!SPIx Bus configuration in HALFDUPLEX */
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY		3	/*!SPIx Bus configuration in SIMPLEX RX ONLY */
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY		4	/*!SPIx Bus configuration in SIMPLEX TX ONLY */


/*
 * @SPI_ClkSpeed
 */

#define SPI_CLK_SPEED_DIV2					0	/*! Clock speed is peripheral clk i.e fclk/2 */
#define SPI_CLK_SPEED_DIV4					1	/*! Clock speed is peripheral clk i.e fclk/4 */
#define SPI_CLK_SPEED_DIV8					2	/*! Clock speed is peripheral clk i.e fclk/8 */
#define SPI_CLK_SPEED_DIV16					3	/*! Clock speed is peripheral clk i.e fclk/16 */
#define SPI_CLK_SPEED_DIV32					4	/*! Clock speed is peripheral clk i.e fclk/32 */
#define SPI_CLK_SPEED_DIV64					5	/*! Clock speed is peripheral clk i.e fclk/64 */
#define SPI_CLK_SPEED_DIV128				6	/*! Clock speed is peripheral clk i.e fclk/128 */
#define SPI_CLK_SPEED_DIV256				7	/*! Clock speed is peripheral clk i.e fclk/256 */

/*
 * @SPI_DFF
 */

#define SPI_DFF_8BITS						0	/*! Data Frame Format is 8 BITS */
#define SPI_DFF_16BITS						1	/*! Data Frame Format is 16 BITS */

/*
 * @CPOL
 */

#define SPI_CPOL_HIGH						1	/*! Clock polarity is HIGH */
#define SPI_CPOL_LOW						0	/*! Clock polarity is LOW */

/*
 * @CPHA
 */


#define SPI_CPHA_HIGH						1	/* Clock Phase is HIGH */
#define SPI_CPHA_LOW						0	/* Clock phase is LOW */



/*
 * @SPI_SSM
 */

#define SPI_SSM_EN							1	/*! Enable the SSM - Software Slave Management */
#define SPI_SSM_DI							0	/*! Disable the SSM - Software Slave Management */


/*
 * SPI related Status flag definitions
 */
#define SPI_TXE_FLAG						(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG						(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG						(1 << SPI_SR_BSY)



/******************************************************************************************************************
 * 												APIs supported by this driver
 * 						     For more information about the APIs check the function definitions
 ******************************************************************************************************************/

/********************************************Peripheral Clock Control**********************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);		/*! SPIx Peripheral Clock control API*/

/******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/

void SPI_Init(SPI_Handle_t *pSPIHandle);								/*! SPIx initialisation API*/

void SPI_DeInit(SPI_RegDef_t *pSPIx);									/*! SPIx Deinitialisation API*/

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);		/*! GET SPI Status Flags */

/******************************************************************************************************************/

/************************************************Data Send/Receive APIs********************************************/

bool SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);		/*! SPIx Send Data API*/

void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer, uint32_t Len);		/*! SPIx Receive Data API*/

bool SPI_TransmitReceive(SPI_RegDef_t *pSPIx,uint8_t *tx_data, uint8_t *rx_data, uint8_t len);	/*! SPIx Transmit and receive byte in a single function */								/*! SPIx Tx and Rx DAta API*/

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);/*! SPIx Send Data Interrupt API*/

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer, uint32_t Len);	/*! SPIx Receive Data Interrupt API*/

/******************************************************************************************************************/


/********************************************IRQ Configuration and ISR Handler*************************************/

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			/*! SPIx IRQ Interrupt Configuration API*/

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);	/*! SPIx IRQ priority number config API*/

void SPI_IRQHandling(SPI_Handle_t *pHandle);							/*! SPIx IRQ/ISR Handler API*/

/******************************************************************************************************************/

/********************************************Other Peripheral Control APIs*****************************************/

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);		/*! SPIx Peripheral control API */

void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);				/*! SPIx Software slave managment API */

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);				/*! SPIx Software slave managment Error API */

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);								/*! SPIx clear overrun flag API */

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);					/*! SPIx Transmission closure API */

void SPI_CloseReception(SPI_Handle_t *pSPIHandle);						/*! SPIx Reception closure API */

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);	/*! SPIx Application callback event for IRQ's */

/******************************************************************************************************************/



#endif /* INC_STM32F446XX_SPI_DRIVER_H_ */
