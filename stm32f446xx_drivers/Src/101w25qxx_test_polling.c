/*
 * 101w25qxx_test_polling.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Narendran Srinivasan
 */


#include "stm32f446xx.h"
#include "string.h"
#include "w25qxx.h"
#include "helper.h"
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
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_14;
	GPIO_Init(&SPIPins);

	// NSS
	// SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	// SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 0;
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_12;
	GPIO_Init(&SPIPins);
	// GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NUM_12, ENABLE);
}

void delay()
{
	for (uint32_t i; i <= 5000000; i++);
}

void SPI2_Inits(void){

	SPI_Handle_t SPI2Handle;

	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_ClkSpeed = SPI_CLK_SPEED_DIV128;
	SPI2Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; // Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2Handle);
}

uint32_t recvData;

void inBuild_LED_Init(void)
{

	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NUM_5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GpioLed);
}

int main(void)
{
    // uint8_t recvData[6] = {0}; // Array to store received data


    // Initialize GPIO pins and SPI2
    SPI2_GPIOInits();
    SPI2_Inits();
    SPI_SSOEConfig(SPI2, ENABLE);

    // Function to get Flash Chip Manufacturer ID using JEDECID
    //W25QXX_JEDECID(SPI2, recvData);

    // Function to get Flash Chip Manufacturer ID
    // W25QXX_MANUFACT_ID(SPI2, recvData);

    // Function to get Flash Chip UID
    // W25QXX_READ_UID(SPI2, recvData);

    // Function to enable/disable the write function
    // writeEnable_Flash();
    W25QXX_WRITE_CONTROL(SPI2, ENABLE);


    return 0;
}

