/*
 * stm32f446xx_gpio_driver.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Narendran Srinivasan
 */

#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"				/*! System Driver header inclusion*/

/*
 * This is a Configuration Structure for a GPIO pin
 */

typedef struct{
	uint8_t	GPIO_PinNumber;				/*! This variable holds the GPIO pin Number @GPIO_PIN_NO */
	uint8_t	GPIO_PinMode;				/*! This variable holds the GPIO pin Mode @GPIO_PIN_MODES*/
	uint8_t	GPIO_PinSpeed;				/*! This variable holds the GPIO pin Speed @GPIO_PIN_SPEED*/
	uint8_t	GPIO_PinPuPdControl;		/*! This variable holds the GPIO pin Push-Pull Control @GPIO_PIN_PUPD*/
	uint8_t	GPIO_PinOType;				/*! This variable holds the GPIO pin Output Type(OpenDrain/Push-Pull)@GPIO_PIN_OTYPES*/
	uint8_t	GPIO_PinAltFunMode;			/*! This variable holds the GPIO pin Alternate Function Mode */
}GPIO_PinConfig_t;



/*
 * This is a handler structure for a GPIO pin
 */

typedef struct{
	// Pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOx;				/*! This holds the base address of the GPIO port to which the pin belongs*/
	GPIO_PinConfig_t GPIO_PinConfig;	/*! This holds GPIO pin configuration settings*/

}GPIO_Handle_t;


/*@GPIO_PIN_MODES
 * GPIO Pin Possible Modes
 */
#define GPIO_MODE_IN		0			/*! GPIO mode as Input*/
#define GPIO_MODE_OUT		1			/*! GPIO mode as Output*/
#define GPIO_MODE_ALTFN		2			/*! GPIO mode as Alternate Function*/
#define GPIO_MODE_ANALOG	3			/*! GPIO mode as Analog*/
#define GPIO_MODE_IT_FT		4			/*! GPIO mode as Interrupt Fall Trigger*/
#define GPIO_MODE_IT_RT		5			/*! GPIO mode as Interrupt rise Trigger*/
#define GPIO_MODE_IT_RFT	6			/*! GPIO mode as Interrupt Fall-rise Trigger*/

/*@GPIO_PIN_OTYPES
 * GPIO Pin possible output types
 */
#define GPIO_OP_TYPE_PP		0			/*! GPIO Output Type as Push-pull*/
#define GPIO_OP_TYPE_OD		1			/*! GPIO Output Type as Open Drain*/

/*@GPIO_PIN_SPEED
 * GPIO Pin possible output speed
 */
#define GPIO_SPEED_LOW		0			/*! GPIO PIN in Low Speed*/
#define GPIO_SPEED_MEDIUM	1			/*! GPIO PIN in Medium Speed*/
#define GPIO_SPEED_FAST		2			/*! GPIO PIN in Fast Speed*/
#define GPIO_SPEED_HIGH		3			/*! GPIO PIN in High Speed*/

/*@GPIO_PIN_PUPD
 * GPIO Pin pull up pull down configuration macros
 */
#define GPIO_NO_PUPD			0		/*! GPIO PIN as No Pull-up & No Pull-down mode*/
#define GPIO_PIN_PU				1		/*! GPIO PIN as Only Pull-up*/
#define GPIO_PIN_PD				2		/*! GPIO PIN as Only Pull-down mode*/

/*@GPIO_PIN_NO
 * GPIO Pin number macros
 */

#define	GPIO_PIN_NUM_0			0		/*! GPIO Pin Number 0  */
#define	GPIO_PIN_NUM_1			1		/*! GPIO Pin Number 1  */
#define	GPIO_PIN_NUM_2			2		/*! GPIO Pin Number 2  */
#define	GPIO_PIN_NUM_3			3		/*! GPIO Pin Number 3  */
#define	GPIO_PIN_NUM_4			4		/*! GPIO Pin Number 4  */
#define	GPIO_PIN_NUM_5			5		/*! GPIO Pin Number 5  */
#define	GPIO_PIN_NUM_6			6		/*! GPIO Pin Number 6  */
#define	GPIO_PIN_NUM_7			7		/*! GPIO Pin Number 7  */
#define	GPIO_PIN_NUM_8			8		/*! GPIO Pin Number 8  */
#define	GPIO_PIN_NUM_9			9		/*! GPIO Pin Number 9  */
#define	GPIO_PIN_NUM_10			10		/*! GPIO Pin Number 10 */
#define	GPIO_PIN_NUM_11			11		/*! GPIO Pin Number 11 */
#define	GPIO_PIN_NUM_12			12		/*! GPIO Pin Number 12 */
#define	GPIO_PIN_NUM_13			13		/*! GPIO Pin Number 13 */
#define	GPIO_PIN_NUM_14			14		/*! GPIO Pin Number 14 */
#define	GPIO_PIN_NUM_15			15		/*! GPIO Pin Number 15 */

/*
 * GPIO AF Mode Macros
 */
#define GPIO_AF_MODE_0			0		/*! GPIO Alternate Function Mode 0 */
#define GPIO_AF_MODE_1			1		/*! GPIO Alternate Function Mode 1 */
#define GPIO_AF_MODE_2			2		/*! GPIO Alternate Function Mode 2 */
#define GPIO_AF_MODE_3			3		/*! GPIO Alternate Function Mode 3 */
#define GPIO_AF_MODE_4			4		/*! GPIO Alternate Function Mode 4 */
#define GPIO_AF_MODE_5			5		/*! GPIO Alternate Function Mode 5 */
#define GPIO_AF_MODE_6			6		/*! GPIO Alternate Function Mode 6 */
#define GPIO_AF_MODE_7			7		/*! GPIO Alternate Function Mode 7 */
#define GPIO_AF_MODE_8			8		/*! GPIO Alternate Function Mode 8 */
#define GPIO_AF_MODE_9			9		/*! GPIO Alternate Function Mode 9 */
#define GPIO_AF_MODE_10			10		/*! GPIO Alternate Function Mode 10*/
#define GPIO_AF_MODE_11			11		/*! GPIO Alternate Function Mode 11*/
#define GPIO_AF_MODE_12			12		/*! GPIO Alternate Function Mode 12*/
#define GPIO_AF_MODE_13			13		/*! GPIO Alternate Function Mode 13*/
#define GPIO_AF_MODE_14			14		/*! GPIO Alternate Function Mode 14*/
#define GPIO_AF_MODE_15			15		/*! GPIO Alternate Function Mode 15*/


/******************************************************************************************************************
 * 												APIs supported by this driver
 * 						     For more information about the APIs check the function definitions
 ******************************************************************************************************************/


/********************************************Peripheral Clock Control**********************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);		/*! GPIO Peripheral Clock control API*/

/******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);												/*! GPIO initialisation API*/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);												/*! GPIO Deinitialisation API*/

/******************************************************************************************************************/

/************************************************Data Read/Write APIs**********************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);				/*! GPIO Read From Input Pin API*/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);									/*! GPIO Read From Input Port API*/

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);	/*! GPIO Write To Ouput Pin API*/

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);						/*! GPIO Write To Output Port API*/

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);					/*! GPIO Pin Toggling API*/

void GPIO_PinControl(GPIO_RegDef_t *pGPIOx, uint16_t GPIO_PinNumber, uint8_t control);

/******************************************************************************************************************/


/********************************************IRQ Configuration and ISR Handler*************************************/

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);						/*! GPIO IRQ Interrupt Configuration API*/

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);					/*! GPIO IRQ priority number config API*/

void GPIO_IRQHandling(uint8_t PinNumber);												/*! GPIO IRQ/ISR Handler API*/

/******************************************************************************************************************/






#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */
