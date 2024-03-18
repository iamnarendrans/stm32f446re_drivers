/*
 * w25qxx.c
 *
 *  Created on: Mar 14, 2024
 *      Author: Narendran Srinivasan
 */

#include "stm32f446xx.h"
#include "w25qxx.h"
#include "helper.h"


bool W25QXX_JEDECID(W25QXX_HandleTypeDef *handle)
{
	bool status = false;
	// Message ID to get Manufacturer ID
	uint8_t tx[4] = {W25QXX_JEDEC_ID, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE};	// Array of Requesting Bytes
	uint8_t rx[4] = {0};
	// int8_t recvData = 0;
	do
	{

		SPI_PeripheralControl(handle->hSPIx, ENABLE);


		if(SPI_TransmitReceive(handle->hSPIx, tx, rx, 4) != H_OK)
		{
			// recvData = rx[1];

			// Delay to ensure the SPI transaction completes (adjust as needed)
			for(uint32_t j = 0; j < 1000; j++);

			SPI_PeripheralControl(handle->hSPIx, DISABLE);

			break;

		}

	    SPI_PeripheralControl(handle->hSPIx, DISABLE);

	    handle->Manufacturer = rx[1];
	    handle->memType = rx[2];
	    handle->size = rx[3];
	    handle->blockCnt = W25QXX_SIZE_BLOCK_COUNT(128);
	    handle->sectorCnt = handle->blockCnt * 16;
	    handle->pageCnt = (handle->sectorCnt * W25QXX_SECTOR_SIZE) / W25QXX_PAGE_SIZE;
	    status = true;

	}while(0);

    return status;

}

uint8_t W25QXX_MANUFACT_ID(SPI_RegDef_t *pSPIx)
{
	// Message ID to get Manufacturer ID
	uint8_t tx[5] = {W25QXX_MANUF_ID, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE, 0x00, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE};	// Array of Requesting Bytes
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
	uint8_t tx[6] = {W25QXX_UID_READ, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE, 0x00, W25QXX_DUMMY_BYTE, W25QXX_DUMMY_BYTE};	// Array of Requesting Bytes
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

bool W25QXX_WRITE_CONTROL(W25QXX_HandleTypeDef *handle, uint8_t EnorDn)
{
	bool status = false;

	uint8_t write_en[1] = {W25QXX_WRITE_EN};
	uint8_t write_di[1] = {W25QXX_WRITE_DI};
	// Enable the flash write
	SPI_PeripheralControl(handle->hSPIx, ENABLE);

	if(EnorDn == ENABLE)
	{

		if(SPI_SendData(handle->hSPIx, write_en, 1) == H_OK)
		{
			// Delay to ensure the SPI transaction completes (adjust as needed)
			for(uint32_t j = 0; j < 100; j++);

			// Disable the flash write
			SPI_PeripheralControl(handle->hSPIx, DISABLE);

			status = true;

			return status;
		}

	}
	else
	{
		// Disable the flash write
		if(SPI_SendData(handle->hSPIx, write_di, 1) == H_OK)
		{
			// Delay to ensure the SPI transaction completes (adjust as needed)
			for(uint32_t j = 0; j < 100; j++);

			// Disable the flash write
			SPI_PeripheralControl(handle->hSPIx, DISABLE);

			status = true;

			return status;

		}

	}

	// Disable the flash write
	SPI_PeripheralControl(handle->hSPIx, DISABLE);

	return status;

}

uint8_t  W25QXX_ReadReg1(SPI_RegDef_t *pSPIx)
{
	uint8_t retVal = 0;
	uint8_t tx[2] = {W25QXX_READ_SR1, W25QXX_DUMMY_BYTE};
	uint8_t rx[2] = {0};

	SPI_PeripheralControl(pSPIx, ENABLE);

	if(SPI_TransmitReceive(pSPIx, tx, rx, 2) == H_OK)
	{
		retVal = rx[1];
	}

	SPI_PeripheralControl(pSPIx, DISABLE);

	return retVal;

}

uint8_t  W25QXX_ReadReg2(SPI_RegDef_t *pSPIx)
{
	uint8_t retVal = 0;
	uint8_t tx[2] = {W25QXX_READ_SR2, W25QXX_DUMMY_BYTE};
	uint8_t rx[2] = {0};

	SPI_PeripheralControl(pSPIx, ENABLE);

	if(SPI_TransmitReceive(pSPIx, tx, rx, 2) == H_OK)
	{
		retVal = rx[1];
	}

	SPI_PeripheralControl(pSPIx, DISABLE);

	return retVal;

}


uint8_t  W25QXX_ReadReg3(SPI_RegDef_t *pSPIx)
{
	uint8_t retVal = 0;
	uint8_t tx[2] = {W25QXX_READ_SR3, W25QXX_DUMMY_BYTE};
	uint8_t rx[2] = {0};

	SPI_PeripheralControl(pSPIx, ENABLE);

	if(SPI_TransmitReceive(pSPIx, tx, rx, 2) == H_OK)
	{
		retVal = rx[1];
	}

	SPI_PeripheralControl(pSPIx, DISABLE);

	return retVal;

}

bool W25QXX_WriteReg1(SPI_RegDef_t *pSPIx, uint8_t data)
{
	bool status = true;
	uint8_t tx[2] = {W25QXX_WRITE_SR1, data};
	uint8_t cmd = W25QXX_WRITE_EN_VOL_SR;

	do
	{
		SPI_PeripheralControl(pSPIx, ENABLE);

		if(SPI_SendData(pSPIx, &cmd, 1) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;
		}

		if(SPI_SendData(pSPIx, tx, 2) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;

		}
		SPI_PeripheralControl(pSPIx, DISABLE);

	}
	while(0);

	return status;
}
bool W25QXX_WriteReg2(SPI_RegDef_t *pSPIx, uint8_t data)
{
	bool status = true;
	uint8_t tx[2] = {W25QXX_WRITE_SR2, data};
	uint8_t cmd = W25QXX_WRITE_EN_VOL_SR;

	do
	{
		SPI_PeripheralControl(pSPIx, ENABLE);

		if(SPI_SendData(pSPIx, &cmd, 1) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;
		}

		if(SPI_SendData(pSPIx, tx, 2) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;

		}
		SPI_PeripheralControl(pSPIx, DISABLE);

	}
	while(0);

	return status;
}

bool W25QXX_WriteReg3(SPI_RegDef_t *pSPIx, uint8_t data)
{
	bool status = true;
	uint8_t tx[2] = {W25QXX_WRITE_SR3, data};
	uint8_t cmd = W25QXX_WRITE_EN_VOL_SR;

	do
	{
		SPI_PeripheralControl(pSPIx, ENABLE);

		if(SPI_SendData(pSPIx, &cmd, 1) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;
		}

		if(SPI_SendData(pSPIx, tx, 2) != H_OK)
		{
			status = false;
			SPI_PeripheralControl(pSPIx, DISABLE);
			break;

		}
		SPI_PeripheralControl(pSPIx, DISABLE);

	}
	while(0);

	return status;
}


bool W25QXX_WaitForWrite(SPI_RegDef_t *pSPIx) // Write timerbased in future After done with timer peripheral
{
	bool status;

	while(1)
	{
		/*
		 * Write one more if condition by passing timeout, after timer concepts done.
		 */

		if((W25QXX_ReadReg1(pSPIx) & W25QXX_STATUS1_BUSY) == 0)
		{
			status = true;
			break;
		}

	}

	return status;
}

void W25QXX_CS_PinControl(W25QXX_HandleTypeDef *handle, uint8_t EnorDn)
{
	SPI_PeripheralControl(handle->hSPIx, EnorDn);
	for(uint8_t i = 0; i<10; i++);
}

bool W25QXX_Init(W25QXX_HandleTypeDef *handle, SPI_RegDef_t *pSPIx)
{
	bool status = false;

	do
	{

		memset(handle, 0, sizeof(W25QXX_HandleTypeDef));
		handle->hSPIx = pSPIx;

		// W25QXX_CS_PinControl(handle, ENABLE); // It Enables the SPI Peripheral, which is CS = 0

		/* Write one timer based check for stable VCC */

//		if(W25QXX_WRITE_CONTROL(handle, DISABLE) == false)
//		{
//			break;
//		}
//
//		for(uint8_t i = 0; i < 100; i++); // Giving some delay

		status = W25QXX_JEDECID(handle);

		if(status)
		{
			handle->initialized = 1;

			// W25QXX_CS_PinControl(handle, DISABLE); // It Enables the SPI Peripheral, which is CS = 0
		}

	}while(0);

	return status;
}
