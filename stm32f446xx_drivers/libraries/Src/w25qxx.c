/*
 * w25qxx.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Narendran Srinivasan
 */

#include "stm32f446xx.h"
#include "w25qxx.h"
#include "helper.h"


void W25QXX_JEDECID(SPI_RegDef_t *pSPIx, uint8_t *recvData)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[4] = {W25QXX_JEDEC_ID, 0xFF, 0xFF, 0xFF};	// Array of Requesting Bytes

	SPI_PeripheralControl(pSPIx, ENABLE);

	for(uint8_t i = 0; i < 4; i++)
	{
		// Transmit and receive response
		recvData[i] = SPI_TransmitReceive(SPI2, tx[i]);

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);
	}
    // Disable SPI2 peripheral
    SPI_PeripheralControl(SPI2, DISABLE);

}

void W25QXX_MANUFACT_ID(SPI_RegDef_t *pSPIx, uint8_t *recvData)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[6] = {W25QXX_MANUF_ID, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};	// Array of Requesting Bytes

	SPI_PeripheralControl(pSPIx, ENABLE);

	for(uint8_t i = 0; i < 6; i++)
	{
		// Transmit and receive response
		recvData[i] = SPI_TransmitReceive(SPI2, tx[i]);

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);
	}
    // Disable SPI2 peripheral
    SPI_PeripheralControl(SPI2, DISABLE);

}


void W25QXX_READ_UID(SPI_RegDef_t *pSPIx, uint8_t *recvData)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[6] = {W25QXX_UID_READ, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	// Array of Requesting Bytes

	SPI_PeripheralControl(pSPIx, ENABLE);

	for(uint8_t i = 0; i < 6; i++)
	{
		// Transmit and receive response
		recvData[i] = SPI_TransmitReceive(SPI2, tx[i]);

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);
	}
    // Disable SPI2 peripheral
    SPI_PeripheralControl(SPI2, DISABLE);

}

void W25QXX_WRITE_CONTROL(SPI_RegDef_t *pSPIx, uint8_t EnorDn)
{
	uint8_t write_en[1] = {W25QXX_WRITE_EN};
	uint8_t write_di[1] = {W25QXX_WRITE_DI};
	// Enable the flash write
	SPI_PeripheralControl(pSPIx, ENABLE);

	if(EnorDn == ENABLE)
	{

		SPI_SendData(pSPIx, write_en, 1);
		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 100; j++);
	}
	else
	{
		// Disable the flash write
		SPI_SendData(pSPIx, write_di, 1);
		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 100; j++);
	}

	// Disable the flash write
	SPI_PeripheralControl(pSPIx, DISABLE);

}

void writeEnable_Flash()
{
	// Disable the flash write
	SPI_PeripheralControl(SPI2, ENABLE);
	uint8_t tx[1] = {W25QXX_UID_READ};
	// GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NUM_12, DISABLE);
	SPI_SendData(SPI2, tx, 1);
	for(uint8_t i = 0; i<=100; i++);
	// GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NUM_12, ENABLE);
//	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NUM_12, RESET);
	// Disable the flash write
	SPI_PeripheralControl(SPI2, DISABLE);
}
