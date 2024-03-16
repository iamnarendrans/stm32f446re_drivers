/*
 * stm32f446xx_clock_driver.c
 *
 *  Created on: Jan 26, 2024
 *      Author: Narendran Srinivasan
 *		E-mail: iamnarendrans@outlook.com
 */

#include "stm32f446xx.h"
#include "stm32f446xx_gpio_driver.h"
#include "stm32f446xx_clock_driver.h"



/********************************************System Clock Control**********************************************/
/******************************************************************************************************************
 * @fn									- CLOCK_HSE_ON
 *
 * @brief								- This function will use the external clock as system clock
 *
 * @param[None]							- None
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void CLOCK_HSE_ON(void)
{
	RCC->CR |= (1 << RCC_CR_HSE_ON);
	while(!(RCC->CR & (1 << RCC_CR_HSE_RDY)));

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- CLOCK_HSE_OFF
 *
 * @brief								- This function will use the external clock as system clock
 *
 * @param[None]							- None
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void CLOCK_HSE_OFF(void)
{
	RCC->CR &= ~(1 << RCC_CR_HSE_ON);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- CLOCK_PLL_ON
 *
 * @brief								- This function will use the PLL clock as system clock
 *
 * @param[None]							- None
 *
 * @return								- None
 *
 * @note								- None
 *****************************************************************************************************************/
void CLOCK_PLL_ON(void)
{
	RCC->CR |= (1 << RCC_CR_PLL_ON);
	while(!(RCC->CR & (1 << RCC_CR_PLL_RDY)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
