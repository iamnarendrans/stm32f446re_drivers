/*
 * SD.h
 *
 *  Created on: Apr 15, 2024
 *      Author: iamna
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include <stdbool.h>

int is_sd_card_mounted(void);

void updateLogFile(const char* TAG, const char* InfoString);

bool isFileExist(const char* filename);

void SDCard_Init(void);

void CharaExtendedCSVFile_Create(void);

void SD_Card_Test(void);

#endif /* INC_SD_H_ */
