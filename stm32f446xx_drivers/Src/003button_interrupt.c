/*
 * 003button_interrupt.c
 *
 *  Created on: Dec 4, 2023
 *      Author: Narendran Srinivasan
 */


#include "stm32f446xx.h"
#include <string.h>

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
	memset(&GpioLed, 0, sizeof(GpioLed));
	memset(&GPIOBtn, 0, sizeof(GPIOBtn));

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&GPIOBtn);

	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NUM_5, GPIO_PIN_RESET);

	// IRQ Configurations
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	while(1);

	return 0;
}


void EXTI15_10_IRQHandler(void)
{
	delay(); 		// To avoid debouncing effect
	GPIO_IRQHandling(GPIO_PIN_NUM_13); // Clear the pending event from EXTI LINE
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NUM_5);
}
