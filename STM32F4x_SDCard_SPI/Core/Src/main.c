/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
char TxBuffer[250];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
static void SD_Card_Test(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void UART_Print(char *str)
{

	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 100);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI3_Init();
  MX_FATFS_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  SD_Card_Test();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI3_CS_GPIO_Port, SPI3_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI3_CS_Pin */
  GPIO_InitStruct.Pin = SPI3_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI3_CS_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
// Planning to use this SD_Card_Test Function for CardLifecycle and usage monitoring
static void SD_Card_Test(void)
{
	FATFS 	FatFs;
	FIL 	Fil;
	FRESULT FR_Status;
	FATFS	*FS_Ptr;
	UINT	RWC, WWC; //Read, Write word counter
	DWORD	FreeClusters;
	uint32_t TotalSize, FreeSpace;
	char	RW_Buff[200];

	do
	{
		//-------------------------------[ Mount the SD Card ]-----------------------------
		FR_Status = f_mount(&FatFs, "", 1);
		if(FR_Status != FR_OK)
		{
			sprintf(TxBuffer, "Error!, While mounting SD Card, Error Code: (%i)\r\n", FR_Status);
			UART_Print(TxBuffer);
			break;
		}
		sprintf(TxBuffer, "SDCard Mounted Successfully! \r\n\n");
		UART_Print(TxBuffer);
		//------------------------[Get & Print SD Card Size & Free Space]------------------
		f_getfree("", &FreeClusters, &FS_Ptr);
		TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
		FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
		sprintf(TxBuffer, "Total SD card Size: %lu Bytes\r\n", TotalSize);
		UART_Print(TxBuffer);
		sprintf(TxBuffer, "Free SD card Space: %lu Bytes\r\n", FreeSpace);
		UART_Print(TxBuffer);
		//-----------------------[Open a Text file for write & Write data]-----------------
		// Open a file
		FR_Status = f_open(&Fil, "TextFileWrite.txt", FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
		if(FR_Status != FR_OK)
		{
			sprintf(TxBuffer, "Error!, In opening/creating a .txt file, Error code : (%i)\r\n", FR_Status);
			UART_Print(TxBuffer);
			break;
		}
		sprintf(TxBuffer, "Text File Created & Opened! Writing Data to the text File\r\n");
		UART_Print(TxBuffer);
		// (1)Write data to the text file [ use f_puts() function]
	    f_puts("Hello! From Kiddy To SD Card Over SPI, Using f_puts()\n", &Fil);
	    // (2) Write Data To The Text File [ Using f_write() Function ]
	    strcpy(RW_Buff, "Hello! From Kiddy To SD Card Over SPI, Using f_write()\r\n");
	    f_write(&Fil, RW_Buff, strlen(RW_Buff), &WWC);
	    // Close the file
	    f_close(&Fil);
	    //-------------------------[Open a Text file for Read & Read data]------------------
	    // Open a file
	    FR_Status = f_open(&Fil, "TextFileWrite.txt", FA_READ);
	    if(FR_Status != FR_OK)
	    {
	    	sprintf(TxBuffer, "Error!, While opening file for read .. \r\n");
	    	UART_Print(TxBuffer);
	    	break;
	    }
	    // (1) Read The Text File's Data [ Using f_gets() Function ]
	    f_gets(RW_Buff, sizeof(RW_Buff), &Fil);
	    sprintf(TxBuffer, "Data Read From (TextFileWrite.txt) Using f_gets():%s", RW_Buff);
	    UART_Print(TxBuffer);
	    // (2) Read The Text File's Data [ Using f_read() Function ]
	    f_read(&Fil, RW_Buff, f_size(&Fil), &RWC);
	    sprintf(TxBuffer, "Data Read From (TextFileWrite.txt) Using f_read():%s", RW_Buff);
	    UART_Print(TxBuffer);
	    // Close The File
	    f_close(&Fil);
	    sprintf(TxBuffer, "File Closed! \r\n\n");
	    UART_Print(TxBuffer);
	    //-----------[ Open An Existing Text File, Update Its Content, Read It Back ]--------
	    // (1) Open The Existing File For Write (Update)
	    FR_Status = f_open(&Fil, "TextFileWrite.txt", FA_OPEN_EXISTING | FA_WRITE);
	    FR_Status = f_lseek(&Fil, f_size(&Fil)); // Move The File Pointer To The EOF (End-Of-File)
	    if(FR_Status != FR_OK)
	    {
	      sprintf(TxBuffer, "Error! While Opening (TextFileWrite.txt) File For Update.. \r\n");
	      UART_Print(TxBuffer);
	      break;
	    }
	    // (2) Write New Line of Text Data To The File
	    FR_Status = f_puts("This New Line Was Added During Update!\r\n", &Fil);
	    f_close(&Fil);
	    memset(RW_Buff,'\0',sizeof(RW_Buff)); // Clear The Buffer
	    // (3) Read The Contents of The Text File After The Update
	    FR_Status = f_open(&Fil, "TextFileWrite.txt", FA_READ); // Open The File For Read
	    f_read(&Fil, RW_Buff, f_size(&Fil), &RWC);
	    sprintf(TxBuffer, "Data Read From (TextFileWrite.txt) After Update:%s", RW_Buff);
	    UART_Print(TxBuffer);
	    f_close(&Fil);
	    //-----------------------------[ Delete The Text File ]---------------------------
	    // Delete The File
	    /*
	    FR_Status = f_unlink(TextFileWrite.txt);
	    if (FR_Status != FR_OK){
	        sprintf(TxBuffer, "Error! While Deleting The (TextFileWrite.txt) File.. \r\n");
	        UART_Print(TxBuffer);
	    }
	    */
	}while(0);
	//-----------------------[Test completed!, Unmount the SDCard]----------------------------
	FR_Status = f_mount(NULL, "", 0);
	if(FR_Status != FR_OK)
	{
		sprintf(TxBuffer, "Error!, While Unmounting the SD card, Error code : (%i)\r\n", FR_Status);
		UART_Print(TxBuffer);
	}
	else
	{
		sprintf(TxBuffer, "SD Card unmounted successfully! \r\n");
		UART_Print(TxBuffer);
	}

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
