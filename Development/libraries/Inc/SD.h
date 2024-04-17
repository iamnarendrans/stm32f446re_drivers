/*
 * SD.h
 *
 *  Created on: Apr 15, 2024
 *      Author: iamna
 */

#ifndef INC_SD_H_
#define INC_SD_H_

#include <stdbool.h>
#include <stdint.h>

uint8_t IsSDCardMounted(void);

void updateLogFile(const char* TAG, const char* InfoString);

bool isFileExist(const char* filename);

void SDCardInit(void);

void UARTExtendedStreamCSVCreate(void);

void UARTSDExtendedStreamWrite(void);

#endif /* INC_SD_H_ */
