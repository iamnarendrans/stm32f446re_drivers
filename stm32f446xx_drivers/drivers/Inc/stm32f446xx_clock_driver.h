/*
 * stm32f446xx_clock_driver.h
 *
 *  Created on: Jan 26, 2024
 *      Author: Narendran Srinivasan
 *		E-mail: iamnarendrans@outlook.com
 */

#ifndef INC_STM32F446XX_CLOCK_DRIVER_H_
#define INC_STM32F446XX_CLOCK_DRIVER_H_

#include "stm32f446xx.h"				/*! System Driver header inclusion*/

#define RCC_CR_HSI_ON		0
#define RCC_CR_HSI_RDY		1
#define RCC_CR_HSI_TRIM		3
#define RCC_CR_HSI_CAL		8
#define RCC_CR_HSE_ON		16
#define RCC_CR_HSE_RDY		17
#define RCC_CR_HSE_BYP		18
#define RCC_CR_CSS_ON		19
#define RCC_CR_PLL_ON		24
#define RCC_CR_PLL_RDY		25
#define RCC_CR_PLL_I2S_ON	26
#define RCC_CR_PLL_I2SRDY	27
#define RCC_CR_PLL_SAI_ON	28
#define RCC_CR_PLL_SAI_RDY	29

/********************************************System Clock Control**********************************************/
void CLOCK_HSE_ON(void);

void CLOCK_HSE_OFF(void);

void CLOCK_PLL_ON(void);

uint32_t RCC_GetPLLOutputClk(void);

uint32_t RCC_GetPCLK1Value(void);

uint32_t RCC_GetPCLK2Value(void);

/**************************************************************************************************************/


#endif /* INC_STM32F446XX_CLOCK_DRIVER_H_ */
