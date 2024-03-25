/*
 * w25qxx.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Narendran Srinivasan
 */

#ifndef LIBRARIES_INC_W25QXX_H_
#define LIBRARIES_INC_W25QXX_H_

#include "stm32f446xx.h"

/*************************************************Register Bytes**************************************************/

#define W25QXX_MANUFACTURER_GIGADEVICE			((uint8_t)0xC8UL)
#define W25QXX_MANUFACTURER_WINBOND				((uint8_t)0xEFUL)

#define W25QXX_DUMMY_BYTE						((uint8_t)0xFFUL)
#define W25QXX_JEDEC_ID							((uint8_t)0x9FUL)
#define W25QXX_MANUF_ID							((uint8_t)0x90UL)

#define W25QXX_WRITE_EN							((uint8_t)0x06UL)
#define W25QXX_WRITE_EN_VOL_SR					((uint8_t)0x50UL)
#define W25QXX_WRITE_DI							((uint8_t)0x04UL)

#define W25QXX_READ_SR1							((uint8_t)0x05UL)
#define W25QXX_READ_SR2							((uint8_t)0x35UL)
#define W25QXX_READ_SR3							((uint8_t)0x15UL)
#define W25QXX_WRITE_SR1						((uint8_t)0x01UL)
#define W25QXX_WRITE_SR2						((uint8_t)0x31UL)
#define W25QXX_WRITE_SR3						((uint8_t)0x11UL)

#define W25QXX_READ_DATA						((uint8_t)0x03UL)
#define W25QXX_FAST_READ						((uint8_t)0x0BUL)
#define W25QXX_PAGE_PROGRAM_3ADD				((uint8_t)0X02UL)
#define W25QXX_PAGE_PROGRAM_4ADD				((uint8_t)0X12UL)

#define W25QXX_SECTOR_ERASE						((uint8_t)0x20UL)
#define W25QXX_32KB_ERASE						((uint8_t)0x52UL)
#define W25QXX_64KB_ERASE						((uint8_t)0xD8UL)
#define W25QXX_CHIP_ERASE						((uint8_t)0xC7UL)

#define W25QXX_REL_PWR_DWN						((uint8_t)0xABUL)
#define W25QXX_PWR_DOWN							((uint8_t)0xB9UL)
#define W25QXX_UID_READ							((uint8_t)0x4BUL)

#define W25QXX_EN_RST							((uint8_t)0x66UL)
#define W25QXX_DEV_RST							((uint8_t)0x99UL)

/******************************************************************************************************************/


#define W25QXX_SIZE_BLOCK_COUNT(SizeInMBIT)		(2 * SizeInMBIT)

#define W25QXX_PAGE_SIZE                      0x100
#define W25QXX_SECTOR_SIZE                    0x1000
#define W25QXX_BLOCK_SIZE                     0x10000

#define W25QXX_PageToSector(PageNumber)      ((PageNumber * W25QXX_PAGE_SIZE) / W25QXX_SECTOR_SIZE)
#define W25QXX_PageToBlock(PageNumber)       ((PageNumber * W25QXX_PAGE_SIZE) / W25QXX_BLOCK_SIZE)
#define W25QXX_SectorToBlock(SectorNumber)   ((SectorNumber * W25QXX_SECTOR_SIZE) / W25QXX_BLOCK_SIZE)
#define W25QXX_SectorToPage(SectorNumber)    ((SectorNumber * W25QXX_SECTOR_SIZE) / W25QXX_PAGE_SIZE)
#define W25QXX_BlockToPage(BlockNumber)      ((BlockNumber * W25QXX_BLOCK_SIZE) / W25QXX_PAGE_SIZE)
#define W25QXX_PageToAddress(PageNumber)     (PageNumber * W25QXX_PAGE_SIZE)
#define W25QXX_SectorToAddress(SectorNumber) (SectorNumber * W25QXX_SECTOR_SIZE)
#define W25QXX_BlockToAddress(BlockNumber)   (BlockNumber * W25QXX_BLOCK_SIZE)
#define W25QXX_AddressToPage(Address)        (Address / W25QXX_PAGE_SIZE)
#define W25QXX_AddressToSector(Address)      (Address / W25QXX_SECTOR_SIZE)
#define W25QXX_AddressToBlock(Address)       (Address / W25QXX_BLOCK_SIZE)

/*
 * Status bit for 3 Status registers
 */

#define W25QXX_STATUS1_BUSY		(1 << 0)
#define W25QXX_STATUS1_WEL 		(1 << 1)
#define W25QXX_STATUS1_BP0 		(1 << 2)
#define W25QXX_STATUS1_BP1 		(1 << 3)
#define W25QXX_STATUS1_BP2 		(1 << 4)
#define W25QXX_STATUS1_TB 		(1 << 5)
#define W25QXX_STATUS1_SEC 		(1 << 6)
#define W25QXX_STATUS1_SRP 		(1 << 7)

#define W25QXX_STATUS2_SRL 		(1 << 8)
#define W25QXX_STATUS2_QE 		(1 << 6)
#define W25QXX_STATUS2_RESERVE1 (1 << 10)
#define W25QXX_STATUS2_LB1 		(1 << 11)
#define W25QXX_STATUS2_LB2 		(1 << 12)
#define W25QXX_STATUS2_LB3 		(1 << 13)
#define W25QXX_STATUS2_CMP 		(1 << 14)
#define W25QXX_STATUS2_SUS 		(1 << 15)

#define W25QXX_STATUS3_RESERVE1 (1 << 16)
#define W25QXX_STATUS3_RESERVE2 (1 << 17)
#define W25QXX_STATUS3_WPS 		(1 << 18)
#define W25QXX_STATUS3_RESERVE3 (1 << 19)
#define W25QXX_STATUS3_RESERVE4 (1 << 20)
#define W25QXX_STATUS3_DRV2 	(1 << 21)
#define W25QXX_STATUS3_DRV1 	(1 << 22)
#define W25QXX_STATUS3_RESERVE5 (1 << 23)


/*
 * Handle structure for W25QXX Flash
 */


typedef struct
{
	SPI_RegDef_t	*hSPIx;
	uint8_t			Manufacturer;
	uint8_t			memType;
	uint8_t			size;
	uint8_t			initialized;
	uint32_t		pageCnt;
	uint32_t		sectorCnt;
	uint32_t		blockCnt;

}W25QXX_HandleTypeDef;

/******************************************************************************************************************
 * 												APIs supported by this driver
 * 						     For more information about the APIs check the function definitions
 ******************************************************************************************************************/

/*************************************************Init and DeInit**************************************************/

bool W25QXX_Init(W25QXX_HandleTypeDef *handle, SPI_RegDef_t *pSPIx);

/******************************************************************************************************************/

/**********************************************Read/Write Register APIs********************************************/

uint8_t  W25QXX_ReadReg1(W25QXX_HandleTypeDef *handle);

uint8_t  W25QXX_ReadReg2(W25QXX_HandleTypeDef *handle);

uint8_t  W25QXX_ReadReg3(W25QXX_HandleTypeDef *handle);

bool W25QXX_WriteReg1(W25QXX_HandleTypeDef *handle, uint8_t data);

bool W25QXX_WriteReg2(W25QXX_HandleTypeDef *handle, uint8_t data);

bool W25QXX_WriteReg3(W25QXX_HandleTypeDef *handle, uint8_t data);

/******************************************************************************************************************/

/*****************************************************Read Write APIs**********************************************/

bool W25QXX_Write(W25QXX_HandleTypeDef *handle, uint32_t pageNumber, uint8_t *data, uint32_t size, uint32_t Offset);

/******************************************************************************************************************/

/***************************************************Other Control APIs*********************************************/

bool W25QXX_JEDECID(W25QXX_HandleTypeDef *handle);

uint8_t W25QXX_MANUFACT_ID(W25QXX_HandleTypeDef *handle);

uint8_t W25QXX_READ_UID(W25QXX_HandleTypeDef *handle);

void W25QXX_CS_PinControl(W25QXX_HandleTypeDef *handle, uint8_t EnorDn);

bool W25QXX_WRITE_CONTROL(W25QXX_HandleTypeDef *handle, uint8_t EnorDn);

bool W25QXX_WaitForWrite(W25QXX_HandleTypeDef *handle); // Write timerbased in future After done with timer peripheral

/******************************************************************************************************************/



#endif /* LIBRARIES_INC_W25QXX_H_ */
