/*
 * 001led_toggle.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Narendran Srinivasan
 */

#include "stm32f446xx.h"

void delay(void)
{
	for (uint32_t i; i <= 500000/2; i++);
}


int main(void)
{
	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GpioLed);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NUM_5);
		delay();
	}

	return 0;
}
