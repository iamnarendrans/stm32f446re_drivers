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
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddr;
	uint8_t  I2C_AckCtrl;
	uint8_t  I2C_FMDutyCycle;
}I2C_Config_t;

/*
 * Handle structure for I2Cx peripheral
 */

typedef struct
{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
}I2C_Handle_t;


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

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr);

void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr);

/******************************************************************************************************************/


/********************************************IRQ Configuration and ISR Handler*************************************/

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);			/*! I2Cx IRQ Interrupt Configuration API*/

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);	/*! I2Cx IRQ priority number config API*/

/******************************************************************************************************************/

/********************************************Other Peripheral Control APIs*****************************************/

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi);

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName);		/*! GET I2C Status Flags */

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEvent);

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
/******************************************************************************************************************/



#endif /* INC_STM32F446XX_I2C_DRIVER_H_ */
