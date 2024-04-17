/*
 * SD.c
 *
 *  Created on: Apr 15, 2024
 *      Author: iamna
 */

/*****************************************************************************************************
                                                INCLUDES
 *****************************************************************************************************/
#include "SD.h"
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "fatfs.h"
#include "user_helper.h"
#include "userconfig.h"
/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/
/*****************************************************************************************************
                                                 MACROS
 *****************************************************************************************************/


/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/


/*****************************************************************************************************
                                          STRUCTURES AND ENUMS
 *****************************************************************************************************/
FATFS 	FatFs;
FIL 	File;
FRESULT FR_Status;
FATFS	*FS_Ptr;
UINT	RWC, WWC; //Read, Write word counter
DWORD	FreeClusters;
/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/


/*****************************************************************************************************
                                          FUNCTION PROTOTYPES
 *****************************************************************************************************/


/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/


/*****************************************************************************************************
                                           VARIABLE DECLARATIONS
 *****************************************************************************************************/
uint32_t TotalSize, FreeSpace;
char	RW_Buff[200];
char 	TxBuffer[500];
char 	Filename[15];
int32_t iTxArr[70];
static bool sdInitialized = false;

/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/


/*****************************************************************************************************
                                          FUNCTION DEFINITIONS
 *****************************************************************************************************/
/*****************************************************************************************************
 * @fn									- is_sd_card_mounted
 *
 * @brief								- This function will be used to check the file-System mounted
 *
 * @param[None]							- None
 *
 * @return								- uint8_t : if mounted, return 1 else return 0
 *
 * @note								- None
 ******************************************************************************************************/
uint8_t is_sd_card_mounted(void) {
	// Check if the File system is mounted
	if (f_mount(&FatFs, "", 1) == FR_OK) {
		// File system mounted successfully
		return 1;
	} else {
		// File system not mounted
		return 0;
	}
}
/*****************************************************************************************************
 * @fn									- updateLogFile
 *
 * @brief								- This function will be used to update log.txt file in every reset
 *
 * @param[None]							- None
 *
 * @return								- None
 *
 * @note								- None
 ******************************************************************************************************/
void updateLogFile(const char* TAG, const char* InfoString)
{
	FIL File;
	FRESULT FR_Status;
	char txBuff[250];
	// Open the file in append mode
	FR_Status = f_open(&File, "log.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_OPEN_APPEND);
	if (FR_Status != FR_OK) {

		// Write Error handler
		return;
	}

	// Write information to the file
	sprintf(txBuff, "%s: %s\r\n", TAG, InfoString);
	f_puts(txBuff, &File);
	f_close(&File);

}
/*****************************************************************************************************
 * @fn									- isFileExist
 *
 * @brief								- This function will be used to check the file exist or not
 *
 * @param[None]							- None
 *
 * @return								- bool - true/false
 *
 * @note								- None
 ******************************************************************************************************/
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
/*****************************************************************************************************
 * @fn									- SDCard_Init
 *
 * @brief								- This function will be used to Initialise SD card and calculate
 * 										  respective total volume size and free space in volume
 *
 * @param[None]							- None
 *
 * @return								- bool - true/false
 *
 * @note								- None
 ******************************************************************************************************/
void SDCard_Init(void)
{
	do
	{
		//----------------------------------[ Mount The SD Card ]----------------------------------------
		FR_Status = f_mount(&FatFs, "", 1);
		if (FR_Status != FR_OK)
		{
			// Write an Error Handler Function
			break;
		}
		//-----------------------------[ Get & Print The SD Card Size & Free Space ]--------------------
		f_getfree("", &FreeClusters, &FS_Ptr);
		TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
		FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
		//----------------------------------------------------------------------------------------------
		for (int i = 0; i < 70; i++)
		{
			iTxArr[i] = INT32_MAX;
		}
	} while(0);
}

void CharaExtendedCSVFile_Create(void)
{

	strcpy(Filename, "DATA0000.csv");

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
				f_printf(&File, "field%d,", i+1);

			}

			// Write a new line character
			f_puts("rowcount", &File);
			f_puts("\n", &File);

			// Close the file
			f_close(&File);
		}

		//--------------------------[ Open An Existing log.txt File, Update Its Content]-----------------------
		sprintf(TxBuffer, "The %s has been created.Total size and free space are %ld and %ld, respectively", Filename, TotalSize, FreeSpace);
		updateLogFile("INFO", TxBuffer);
		sdInitialized = true;
	}
}

void SD_Card_Test(void) {

	// Define local variables
	FIL csv_File;   // File object
	static uint32_t sd_count = 0;

	// Check if the SD card is mounted
	if (sdInitialized  == true)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		// Open the CSV File
		if (f_open(&csv_File, Filename, FA_OPEN_APPEND | FA_WRITE) == FR_OK)
		{
			// Write the count to the File
			for(uint8_t i = 0; i < SD_NUM_COLUMNS; i++)
			{

				f_printf(&csv_File, "%ld,", iTxArr[i]);

			}

			f_printf(&csv_File, "%ld\n", sd_count + 1);

			// Close the File
			f_close(&csv_File);
		} else
		{
			// Write Error handler function
		}
		sd_count++;
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	}
	else
	{
		// Write Error handler function
	}


}

/*****************************************************************************************************/
//----------------------------------------------------------------------------------------------------/


/*####################################################################################################
####################################################################################################*/






