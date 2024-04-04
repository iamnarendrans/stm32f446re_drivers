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


/****************************************************************************************************************
 * 													PRIVATE VARIABLES
 ****************************************************************************************************************/

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB1_PreScaler[4] = { 2, 4 , 8, 16};

/****************************************************************************************************************/



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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/******************************************************************************************************************
 * @fn									- RCC_GetPCLK2Value
 *
 * @brief								- This function returns the peripheral 1 clock value
 *
 * @param[None]							- None
 *
 * @return								- APB1 clock value
 *
 * @note								- None
 *****************************************************************************************************************/

uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t SystemClock=0,tmp,pclk2;
	uint8_t clk_src = ( RCC->CFRG >> 2) & 0X3;

	uint8_t ahbp,apb2p;

	if(clk_src == 0)
	{
		SystemClock = 16000000;
	}else
	{
		SystemClock = 8000000;
	}
	tmp = (RCC->CFRG >> 4 ) & 0xF;

	if(tmp < 0x08)
	{
		ahbp = 1;
	}else
	{
       ahbp = AHB_PreScaler[tmp-8];
	}

	tmp = (RCC->CFRG >> 13 ) & 0x7;
	if(tmp < 0x04)
	{
		apb2p = 1;
	}else
	{
		apb2p = APB1_PreScaler[tmp-4];
	}

	pclk2 = (SystemClock / ahbp )/ apb2p;

	return pclk2;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
