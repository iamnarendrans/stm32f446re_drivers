/*
 * w25qxx.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Narendran Srinivasan
 */

#include "stm32f446xx.h"
#include "w25qxx.h"
#include "helper.h"


uint8_t W25QXX_JEDECID(SPI_RegDef_t *pSPIx)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[3] = {W25QXX_JEDEC_ID, 0xFF, 0xFF, 0xFF};	// Array of Requesting Bytes
	uint8_t rx[3] = {0};
	uint8_t recvData = 0;

	SPI_PeripheralControl(pSPIx, ENABLE);


	if(SPI_TransmitReceive(pSPIx, tx, rx, 3) == H_OK)
	{
		recvData = rx[1];

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);

		SPI_PeripheralControl(pSPIx, DISABLE);

		return recvData;

	}

    SPI_PeripheralControl(SPI2, DISABLE);

    return recvData;

}

uint8_t W25QXX_MANUFACT_ID(SPI_RegDef_t *pSPIx)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[5] = {W25QXX_MANUF_ID, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};	// Array of Requesting Bytes
	uint8_t rx[5] = {0};
	uint8_t recvData = 0;
	SPI_PeripheralControl(pSPIx, ENABLE);

	if(SPI_TransmitReceive(pSPIx, tx, rx, 5) == H_OK)
	{
		recvData = rx[4];

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);

		SPI_PeripheralControl(pSPIx, DISABLE);

		return recvData;

	}

    SPI_PeripheralControl(SPI2, DISABLE);

    return recvData;

}


uint8_t W25QXX_READ_UID(SPI_RegDef_t *pSPIx)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[6] = {W25QXX_UID_READ, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};	// Array of Requesting Bytes
	uint8_t rx[6] = {0};
	uint8_t recvData = 0;
	SPI_PeripheralControl(pSPIx, ENABLE);

	if(SPI_TransmitReceive(pSPIx, tx, rx, 5) == H_OK)
	{
		recvData = rx[5];

		// Delay to ensure the SPI transaction completes (adjust as needed)
		for(uint32_t j = 0; j < 1000; j++);

		SPI_PeripheralControl(pSPIx, DISABLE);

		return recvData;

	}

    SPI_PeripheralControl(SPI2, DISABLE);

    return recvData;

}

void W25QXX_WRITE_CONTROL(SPI_RegDef_t *pSPIx, uint8_t EnorDn)
{
	uint8_t write_en[1] = {W25QXX_WRITE_EN};
	uint8_t write_di[1] = {W25QXX_WRITE_DI};
	// Enable the flash write
	SPI_PeripheralControl(pSPIx, ENABLE);

	if(EnorDn == ENABLE)
	{

		if(SPI_SendData(pSPIx, write_en, 1) == H_OK)
		{
			// Delay to ensure the SPI transaction completes (adjust as needed)
			for(uint32_t j = 0; j < 100; j++);

			// Disable the flash write
			SPI_PeripheralControl(pSPIx, DISABLE);

			return 0;
		}

	}
	else
	{
		// Disable the flash write
		if(SPI_SendData(pSPIx, write_di, 1) == H_OK)
		{
			// Delay to ensure the SPI transaction completes (adjust as needed)
			for(uint32_t j = 0; j < 100; j++);

			// Disable the flash write
			SPI_PeripheralControl(pSPIx, DISABLE);

			return 0;

		}

	}

	// Disable the flash write
	SPI_PeripheralControl(pSPIx, DISABLE);

}

