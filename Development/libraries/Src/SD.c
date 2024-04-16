/*
 * SD.c
 *
 *  Created on: Apr 15, 2024
 *      Author: iamna
 */

#include "SD.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "fatfs.h"
#include "user_helper.h"
#include "userconfig.h"

FATFS 	FatFs;
FIL 	File;
FRESULT FR_Status;
FATFS	*FS_Ptr;
UINT	RWC, WWC; //Read, Write word counter
DWORD	FreeClusters;
uint32_t TotalSize, FreeSpace;
char	RW_Buff[200];
char TxBuffer[500];
static bool sdInitialized = false;

// Function to check if the SD card is mounted
int is_sd_card_mounted(void) {
	// Check if the File system is mounted
	if (f_mount(&FatFs, "", 1) == FR_OK) {
		// File system mounted successfully
		return 1;
	} else {
		// File system not mounted
		return 0;
	}
}


void updateLogFile(const char* TAG, const char* InfoString)
{
    FIL File;
    FRESULT FR_Status;
    char txBuff[250];
    // Open the file in append mode
    FR_Status = f_open(&File, "log.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_OPEN_APPEND);
    if (FR_Status != FR_OK) {

        sprintf(TxBuffer, "Error! While Opening File For Update.. \r\n");
        UART_Print(TxBuffer);
        return;
    }

    // Write information to the file
    sprintf(txBuff, "%s: %s\r\n", TAG, InfoString);
    f_puts(txBuff, &File);
    f_close(&File);

}


bool isFileExist(const char* filename) {
	FILINFO fno; // Gathering file info, if not needed keep it NULL
	FRESULT fr;
	fr = f_stat(filename, &fno);
	if(fr == FR_NO_FILE)
	{
		return false; // File not exist
	}

	return true;	// File already exist
}

void SDCard_Init(void)
{
#if UART_ENABLED == 1
	do
	{
		//----------------------------------[ Mount The SD Card ]----------------------------------------
		FR_Status = f_mount(&FatFs, "", 1);
		if (FR_Status != FR_OK)
		{
			sprintf(TxBuffer, "Error! While Mounting SD Card, Error Code: (%i)\r\n", FR_Status);
			UART_Print(TxBuffer);
			break;
		}
		sdInitialized = true;
		sprintf(TxBuffer, "SD Card Mounted Successfully! \r\n\n");
		UART_Print(TxBuffer);
		//-----------------------------[ Get & Print The SD Card Size & Free Space ]--------------------
		f_getfree("", &FreeClusters, &FS_Ptr);
		TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
		FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
		//----------------------------------------------------------------------------------------------
	} while(0);
#else
	// Execute the remaining lines if UART is not enabled
	FR_Status = f_mount(&FatFs, "", 1);
	if (FR_Status != FR_OK)
	{
		// Handle the error
	}
	//-----------------------------[ Get & Print The SD Card Size & Free Space ]--------------------
	f_getfree("", &FreeClusters, &FS_Ptr);
	TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
	FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
	//----------------------------------------------------------------------------------------------
#endif
}

void CharaExtendedCSVFile_Create(void)
{
	char Filename[15];
	char fieldStr[10];
	strcpy(Filename, "data0000.csv");

	for(uint16_t i = 0; i < SD_NUM_OF_FILES; i++)
	{
		Filename[4] = '0' + i / 1000; // Thousands digit
		Filename[5] = '0' + i / 100; // Hundreds digit
		Filename[6] = '0' + i / 10; // Tens digit
		Filename[7] = '0' + i % 10; // Ones digit

		// Check if the file already exists
		if(!isFileExist(Filename))
		{
			break;
		}
	}

	// Check if the SD card is mounted
	if (is_sd_card_mounted())
	{
		// Open the CSV File
		if (f_open(&File, Filename, FA_OPEN_ALWAYS | FA_WRITE) == FR_OK)
		{
			for(uint8_t i = 0; i < SD_NUM_COLUMNS; i++)
			{
				sprintf(fieldStr, "field%d", i+1);

				// Write field string to the file
				f_puts(fieldStr, &File);

				if(i < SD_NUM_COLUMNS - 1) // Corrected the condition to avoid writing extra comma
				{
					// Write comma if it's not the last field
					f_puts(",", &File);
				}
			}

			// Write a new line character
			f_puts("\n", &File);

			// Close the file
			f_close(&File);
		}

		//--------------------------[ Open An Existing log.txt File, Update Its Content]-----------------------
		sprintf(TxBuffer, "The %s has been created.Total size and free space are %ld and %ld, respectively", Filename, TotalSize, FreeSpace);
		updateLogFile("INFO", TxBuffer);
	}
}



void SD_Card_Test(void) {
//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	// Define local variables
	FIL csv_File;   // File object
	static uint32_t sd_count = 0;

	// Check if the SD card is mounted
	if (sdInitialized  == true)
	{ // You need to define this function
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		// Open the CSV File
		if (f_open(&csv_File, "data.csv", FA_OPEN_ALWAYS | FA_WRITE) == FR_OK)
		{
			// Move to the end of the File
			f_lseek(&csv_File, f_size(&csv_File));

			// Write the count to the File
			f_printf(&csv_File, "%lu\n", sd_count);
//			sprintf(TxBuffer, "The corresponding count %ld\r\n", sd_count);
//			UART_Print(TxBuffer);

			// Close the File
			f_close(&csv_File);
		} else
		{
//			 UART_Print("Error: Unable to open the File.\r\n");
		}
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	}
	else
	{
//		 UART_Print("Error: SD card not mounted.\r\n");
	}

	sd_count++;


}

