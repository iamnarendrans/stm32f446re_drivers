/*
 * 004spi_tx_testing.c
 *
 *  Created on: Dec 8, 2023
 *      Author: Narendran Srinivasan
 */

#include "stm32f446xx.h"
#include "string.h"

/*
 * PB12 --> SPI2_NSS
 * PB13 --> SPI2_SCK
 * PB14 --> SPI2_MISO
 * PB15 --> SPI2_MOSI
 * ALT Function Mode - 5
 */

void SPI2_GPIOInits(void){

	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	// SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_13;
	GPIO_Init(&SPIPins);

	// MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_15;
	GPIO_Init(&SPIPins);

	// MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_14;
	//GPIO_Init(&SPIPins);

	// NSS
	// SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_12;
	// GPIO_Init(&SPIPins);
}

void SPI2_Inits(void){

	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_ClkSpeed = SPI_CLK_SPEED_DIV256;
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_HIGH;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_HIGH;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_EN; // Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2Handle);
}


int main(void)
{
	char userData[] = " Hello World";
	// This function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	// This function is used to initialize the SPI2 peripherals parameters
	SPI2_Inits();

	// This makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI2, ENABLE);

	// This enables the SPI2 peripheral
	SPI_PeripheralControl(SPI2, ENABLE);

	// to send data
	SPI_SendData(SPI2, (uint8_t*)userData, strlen(userData));

	// This disables the SPI2 peripheral
	SPI_PeripheralControl(SPI2, DISABLE);

	while(1);

	return 0;
}
