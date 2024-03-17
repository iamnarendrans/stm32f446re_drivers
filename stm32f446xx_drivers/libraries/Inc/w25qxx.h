/*
 * w25qxx.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Narendran Srinivasan
 */

#ifndef LIBRARIES_INC_W25QXX_H_
#define LIBRARIES_INC_W25QXX_H_

#include "stm32f446xx.h"


#define W25QXX_MANUFACTURER_GIGADEVICE	0xC8
#define W25QXX_MANUFACTURER_WINBOND		0xEF


#define W25QXX_DUMMY_BYTE				0xA5
#define W25QXX_JEDEC_ID					0x9F
#define W25QXX_MANUF_ID					0x90

#define W25QXX_WRITE_EN					0x06
#define W25QXX_WRITE_EN_VOL_SR			0x50
#define W25QXX_WRITE_DI					0x04

#define W25QXX_READ_SR1					0x05
#define W25QXX_READ_SR2					0x35
#define W25QXX_READ_SR3					0x15
#define W25QXX_WRITE_SR1				0x01
#define W25QXX_WRITE_SR2				0x31
#define W25QXX_WRITE_SR3				0x11

#define W25QXX_READ_DATA				0x03
#define W25QXX_FAST_READ				0x0B
#define W25QXX_PAGE_PROGRAM				0X02

#define W25QXX_SECTOR_ERASE				0x20
#define W25QXX_32KB_ERASE				0x52
#define W25QXX_64KB_ERASE				0xD8
#define W25QXX_CHIP_ERASE				0xC7

#define W25QXX_REL_PWR_DWN				0xAB
#define W25QXX_PWR_DOWN					0xB9
#define W25QXX_UID_READ					0x4B

#define W25QXX_EN_RST					0x66
#define W25QXX_DEV_RST					0x99

#define W25QXX_PAGE_SIZE                      0x100
#define W25QXX_SECTOR_SIZE                    0x1000
#define W25QXX_BLOCK_SIZE                     0x10000

#define W25QXX_PageToSector(PageNumber)      ((PageNumber * SPIF_PAGE_SIZE) / SPIF_SECTOR_SIZE)
#define W25QXX_PageToBlock(PageNumber)       ((PageNumber * SPIF_PAGE_SIZE) / SPIF_BLOCK_SIZE)
#define W25QXX_SectorToBlock(SectorNumber)   ((SectorNumber * SPIF_SECTOR_SIZE) / SPIF_BLOCK_SIZE)
#define W25QXX_SectorToPage(SectorNumber)    ((SectorNumber * SPIF_SECTOR_SIZE) / SPIF_PAGE_SIZE)
#define W25QXX_BlockToPage(BlockNumber)      ((BlockNumber * SPIF_BLOCK_SIZE) / SPIF_PAGE_SIZE)
#define W25QXX_PageToAddress(PageNumber)     (PageNumber * SPIF_PAGE_SIZE)
#define W25QXX_SectorToAddress(SectorNumber) (SectorNumber * SPIF_SECTOR_SIZE)
#define W25QXX_BlockToAddress(BlockNumber)   (BlockNumber * SPIF_BLOCK_SIZE)
#define W25QXX_AddressToPage(Address)        (Address / SPIF_PAGE_SIZE)
#define W25QXX_AddressToSector(Address)      (Address / SPIF_SECTOR_SIZE)
#define W25QXX_AddressToBlock(Address)       (Address / SPIF_BLOCK_SIZE)


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


uint8_t W25QXX_JEDECID(SPI_RegDef_t *pSPIx);

uint8_t W25QXX_MANUFACT_ID(SPI_RegDef_t *pSPIx);

uint8_t W25QXX_READ_UID(SPI_RegDef_t *pSPIx);

void W25QXX_WRITE_CONTROL(SPI_RegDef_t *pSPIx, uint8_t EnorDn);

void W25QXX_VOL_WRITE_EN(SPI_RegDef_t *pSPIx);

uint8_t  W25QXX_ReadReg1(SPI_RegDef_t *pSPIx);
uint8_t  W25QXX_ReadReg2(SPI_RegDef_t *pSPIx);
uint8_t  W25QXX_ReadReg3(SPI_RegDef_t *pSPIx);




#endif /* LIBRARIES_INC_W25QXX_H_ */
