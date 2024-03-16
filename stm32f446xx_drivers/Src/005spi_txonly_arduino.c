/*
 * 005spi_txonly_arduino.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Narendran Srinivasan
 */


#include <string.h>
#include "stm32f446xx.h"

/*
 * PB12 --> SPI2_NSS
 * PB13 --> SPI2_SCK
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * ALT Function Mode - 5
 */

void delay()
{
	for (uint32_t i; i <= 500000/2; i++);
}


void SPI2_GPIOInits(void){
	GPIO_Handle_t SPIPins;
	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIO_Init(&SPIPins);

	// MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_15;
	GPIO_Init(&SPIPins);

	// MISO
	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_14;
	// GPIO_Init(&SPIPins);

	// NSS
	 SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_12;
	 GPIO_Init(&SPIPins);
}

void SPI2_Inits(void){
	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_ClkSpeed = SPI_CLK_SPEED_DIV4; // Generates the SCLK of 2Mhz
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2Handle);

}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PD;

	GPIO_Init(&GPIOBtn);

}

int main(void)
{
	char user_data[] = "Hello world";

	GPIO_ButtonInit();

	//This function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	// This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	/*
	 * Making SSOE 1 does NSS output enable.
	 * This NSS Pin is automatically managed by the hardware
	 * i.e when SPE = 1, NSS will be pulled to low
	 * and NSS pin will be high when SPE = 0
	 */
	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{
		while(!(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NUM_13)));

		// To avoid button de-bouncing related issues 200ms of delay
		delay(200);

		// Enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2, ENABLE);

		// First send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2, &dataLen, 1);

		// This function is used to send the data over SPI2 peripheral
		SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

		// Lets confirm SPI is not busy
		while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));

		// Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2, DISABLE);
	}

	return 0;
}
