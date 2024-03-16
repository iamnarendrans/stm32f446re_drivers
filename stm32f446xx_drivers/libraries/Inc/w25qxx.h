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


void writeEnable_Flash();

void W25QXX_JEDECID(SPI_RegDef_t *pSPIx, uint8_t *recvData);

void W25QXX_MANUFACT_ID(SPI_RegDef_t *pSPIx, uint8_t *recvData);

void W25QXX_READ_UID(SPI_RegDef_t *pSPIx, uint8_t *recvData);

void W25QXX_WRITE_CONTROL(SPI_RegDef_t *pSPIx, uint8_t EnorDn);



#endif /* LIBRARIES_INC_W25QXX_H_ */
