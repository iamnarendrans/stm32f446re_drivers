/*
 * stm32f446xx_i2c_driver.h
 *
 *  Created on: Jan 1, 2024
 *      Author: Narendran Srinivasan
 *		E-mail: iamnarendrans@outlook.com
 */

#ifndef INC_STM32F446XX_I2C_DRIVER_H_
#define INC_STM32F446XX_I2C_DRIVER_H_

#include "stm32f446xx.h"				/*! System Driver header inclusion*/

/*
 * Configuration structure for I2Cx peripheral
 */

typedef struct
{
	uint32_t I2C_SCLSpeed;			/*! Configuration of I2Cx bus speed */
	uint8_t  I2C_DeviceAddr;		/*! Configuration of I2Cx master device address */
	uint8_t  I2C_AckCtrl;			/*! Configuration of ACK/NACK control */
	uint8_t  I2C_FMDutyCycle;		/*! Configuration of I2Cx bus Duty Cycle */
}I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 */

typedef struct
{
	I2C_RegDef_t	*pI2Cx;			/*! Base address of the corresponding I2Cx */
	I2C_Config_t	I2C_Config;		/*! I2C Configuration structure */
	uint8_t			*pTxBuffer;		/*! To store the app. Tx Buffer Address */
	uint8_t			*pRxBuffer;		/*! To store the app. Rx Buffer Address */
	uint32_t		TxLen;			/*! To store the Tx Length */
	uint32_t		RxLen;			/*! To store the Rx Length */
	uint8_t			TxRxState;		/*! To store the Communication state */
	uint8_t			DevAddr;		/*! To store slave/device address */
	uint32_t		RxSize;			/*! To store Rx size */
	uint8_t			Sr;				/*! To store repeated start condition */
}I2C_Handle_t;


/*
 * I2C Application States
 */
#define I2C_READY			0		/*! I2C Bus in Ready State */
#define I2C_BUSY_IN_RX		1		/*! I2C Bus in Rx State */
#define I2C_BUSY_IN_TX		2		/*! I2C Bus in Tx State */


/*
 * @I2C_SCLSpeed
 */

#define I2C_SCL_SPEED_SM		100000		/*! I2C bus clock speed in standard mode - 100Kb/s */
#define I2C_SCL_SPEED_FM2K		200000		/*! I2C bus clock speed in standard mode - 200Kb/s */
#define I2C_SCL_SPEED_FM4K		400000		/*! I2C bus clock speed in standard mode - 400Kb/s */

/*
 *@I2C_DeviceAddr - Given by the user only, don't have initializations
 */


/*
 * @I2C_AckCtrl
 */


#define I2C_ACK_EN			1		/*! I2C bus is ready to Acknowledege enable */
#define I2C_ACK_DI			0		/*! I2C bus is ready to Acknowledege disable */

/*
 * @I2C_FMDutyCycle
 */

#define I2C_FM_DUTY_2		0		/*! I2C bus Duty Cyle */
#define I2C_FM_DUTY_19_9	1		/*! I2C bus Duty Cyle */

/*
 * I2C related Status flag definitions
 */
#define I2C_FLAG_TXE						(1 << I2C_SR1_TxE)
#define I2C_FLAG_RXNE						(1 << I2C_SR1_RxNE)
#define I2C_FLAG_SB							(1 << I2C_SR1_SB)
#define I2C_FLAG_OVR						(1 << I2C_SR1_OVR)
#define I2C_FLAG_AF							(1 << I2C_SR1_AF)
#define I2C_FLAG_ARLO						(1 << I2C_SR1_ARLO)
#define I2C_FLAG_BERR						(1 << I2C_SR1_BERR)
#define I2C_FLAG_STOPF						(1 << I2C_SR1_STOPF)
#define I2C_FLAG_ADD10						(1 << I2C_SR1_ADD10)
#define I2C_FLAG_BTF						(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADDR						(1 << I2C_SR1_ADDR)
#define I2C_FLAG_TIMEOUT					(1 << I2C_SR1_TIMEOUT)


#define I2C_DISABLE_SR		RESET
#define I2C_ENABLE_SR		SET

/*
 * I2C Application event macros
 */

#define I2C_EV_TX_CMPLT		0
#define I2C_EV_RX_CMPLT		1
#define I2C_EV_STOP			2
#define I2C_ERROR_BERR  	3
#define I2C_ERROR_ARLO  	4
#define I2C_ERROR_AF    	5
#define I2C_ERROR_OVR   	6
#define I2C_ERROR_TIMEOUT 	7
#define I2C_EV_DATA_REQ		8
#define I2C_EV_DATA_RCV		9



/******************************************************************************************************************
 * 												APIs supported by this driver
 * 						     For more information about the APIs check the function definitions
 ******************************************************************************************************************/

/********************************************Peripheral Clock Control**********************************************/

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);		/*! I2Cx Peripheral Clock control API*/

/******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/

void I2C_Init(I2C_Handle_t *pI2CHandle);								/*! I2Cx initialisation API*/

void I2C_DeInit(I2C_RegDef_t *pI2Cx);									/*! I2Cx Deinitialisation API*/

/******************************************************************************************************************/

/************************************************Data Send/Receive APIs********************************************/

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);

uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr);

void I2C_CloseSendData(I2C_Handle_t *pI2CHandle);

void I2C_CloseReceiveData(I2C_Handle_t *pI2CHandle);

void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx, uint8_t data);

uint8_t I2C_SlaveReceiveData(I2C_RegDef_t *pI2Cx);

/******************************************************************************************************************/


/********************************************IRQ Configuration and ISR Handler*************************************/

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			/*! I2Cx IRQ Interrupt Configuration API*/

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);	/*! I2Cx IRQ priority number config API*/

void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle);						/*! I2Cx IRQ Event Handle API*/

void I2C_ERR_IRQHandling(I2C_Handle_t *pI2CHandle);						/*! I2Cx IRQ Error Handle API*/

/******************************************************************************************************************/

/********************************************Other Peripheral Control APIs*****************************************/

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);		/*! I2Cx peripheral control API */

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);		/*! GET I2C Status Flags */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent);	/*! I2Cx Application callback event for IRQ's */

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);				/*! I2Cx ACK/NACK Management API */

void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
/******************************************************************************************************************/



#endif /* INC_STM32F446XX_I2C_DRIVER_H_ */
