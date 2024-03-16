/*
 * 002led_button.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Narendran Srinivasan
 */


#include "stm32f446xx.h"

#define HIGH	1
#define LOW		0
#define BTN_PRESSED	LOW

void delay()
{
	for (uint32_t i; i <= 500000; i++);
}


int main(void)
{
	GPIO_Handle_t GpioLed, GPIOBtn;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

	GPIO_Init(&GPIOBtn);

	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NUM_13) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NUM_5);
		}


	}
	return 0;
}
