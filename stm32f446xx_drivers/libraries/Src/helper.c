/*
 * helper.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Narendran Srinivasan
 */

#ifndef INC_HELPER_C_
#define INC_HELPER_C_

#include "stm32f446xx.h"
#include "stdint.h"

uint32_t h_strLen(const char *str)
{
	uint32_t len;
	for(len = 0; str[len] != '\0'; len++);
	return len;
}

void h_delay(uint32_t delay_in_S)  // Still pending and needs to be tested
{
	static uint32_t SystemClk;

	uint8_t clksrc;

	clksrc = ((RCC->CFRG >> 2) & 0x3);

	if (clksrc == 0)
	{
		SystemClk = 16000000;
	}else if (clksrc == 1)
	{
		SystemClk = 8000000;
	}else if (clksrc == 2)
	{
		// Write it in future
	}

	uint32_t delayCycle = delay_in_S * SystemClk;

	for(uint32_t i = 0; i < delayCycle; i++);


}

void hsi_delay(uint32_t delay_in_s) // tested for 1s delay
{

	for(uint32_t i = 0; i <= (900000 * delay_in_s); i++);
}

#endif /* INC_HELPER_C_ */
