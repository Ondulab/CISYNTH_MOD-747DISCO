/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "config.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t qspi_aTxBuffer[BUFFER_SIZE];
uint8_t qspi_aRxBuffer[BUFFER_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void QSPI_SetHint(void);
static void Fill_Buffer(uint8_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

/**
 * @brief  QSPI Init
 * @param  None
 * @retval None
 */
void QSPI_Init(void)
{
	/* QSPI info structure */
	BSP_QSPI_Info_t pQSPI_Info;
	uint8_t status;

	/*##-1- Configure the QSPI device ##########################################*/
	/* QSPI device configuration */
	BSP_QSPI_Init_t init ;
	init.InterfaceMode=MT25TL01G_QPI_MODE;
	init.TransferRate= MT25TL01G_DTR_TRANSFER ;
	init.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
	status = BSP_QSPI_Init(0,&init);

	if (status != BSP_ERROR_NONE)
	{
		Error_Handler();
	}
	else
	{
		/*##-2- Read & check the QSPI info #######################################*/
		/* Initialize the structure */
		pQSPI_Info.FlashSize          = (uint32_t)0x00;
		pQSPI_Info.EraseSectorSize    = (uint32_t)0x00;
		pQSPI_Info.EraseSectorsNumber = (uint32_t)0x00;
		pQSPI_Info.ProgPageSize       = (uint32_t)0x00;
		pQSPI_Info.ProgPagesNumber    = (uint32_t)0x00;

		/* Read the QSPI memory info */
		BSP_QSPI_GetInfo(0,&pQSPI_Info);

		/* Test the correctness */
		if((pQSPI_Info.FlashSize != 0x8000000) || (pQSPI_Info.EraseSectorSize != 0x2000)  ||
				(pQSPI_Info.ProgPageSize != 0x100)  || (pQSPI_Info.EraseSectorsNumber != 0x4000) ||
				(pQSPI_Info.ProgPagesNumber != 0x80000))
		{
			Error_Handler();
		}
	}
}

/**
 * @brief  QSPI Demo
 * @param  None
 * @retval None
 */
void QSPI_Demo(void)
{
	/* QSPI info structure */
	BSP_QSPI_Info_t pQSPI_Info;
	uint8_t status;

	QSPI_SetHint();

	/*##-1- Configure the QSPI device ##########################################*/
	/* QSPI device configuration */
	BSP_QSPI_Init_t init ;
	init.InterfaceMode=MT25TL01G_QPI_MODE;
	init.TransferRate= MT25TL01G_DTR_TRANSFER ;
	init.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
	status = BSP_QSPI_Init(0,&init);

	if (status != BSP_ERROR_NONE)
	{
	}

	else
	{
		/*##-2- Read & check the QSPI info #######################################*/
		/* Initialize the structure */
		pQSPI_Info.FlashSize          = (uint32_t)0x00;
		pQSPI_Info.EraseSectorSize    = (uint32_t)0x00;
		pQSPI_Info.EraseSectorsNumber = (uint32_t)0x00;
		pQSPI_Info.ProgPageSize       = (uint32_t)0x00;
		pQSPI_Info.ProgPagesNumber    = (uint32_t)0x00;

		/* Read the QSPI memory info */
		BSP_QSPI_GetInfo(0,&pQSPI_Info);

		/* Test the correctness */
		if((pQSPI_Info.FlashSize != 0x8000000) || (pQSPI_Info.EraseSectorSize != 0x2000)  ||
				(pQSPI_Info.ProgPageSize != 0x100)  || (pQSPI_Info.EraseSectorsNumber != 0x4000) ||
				(pQSPI_Info.ProgPagesNumber != 0x80000))
		{
		}
		else
		{
			/*##-3- Erase QSPI memory ################################################*/
			if(BSP_QSPI_EraseBlock(0,WRITE_READ_ADDR,BSP_QSPI_ERASE_8K) != BSP_ERROR_NONE)
			{
			}
			else
			{
				/*##-4- QSPI memory read/write access  #################################*/
				/* Fill the buffer to write */
				Fill_Buffer(qspi_aTxBuffer, BUFFER_SIZE, 0xD20F);

				/* Write data to the QSPI memory */
				if(BSP_QSPI_Write(0,qspi_aTxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
				{
				}
				else
				{
					/* Read back data from the QSPI memory */
					if(BSP_QSPI_Read(0,qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
					{
					}
					else
					{
						/*##-5- Checking data integrity ############################################*/
						if(Buffercmp(qspi_aRxBuffer, qspi_aTxBuffer, BUFFER_SIZE) > 0)
						{
						}
						else
						{
							/*##-6-Memory Mapped Mode ###############################################*/
							if(BSP_QSPI_EnableMemoryMappedMode(0)!=BSP_ERROR_NONE)
							{
							}
							else
							{
							}
						}
					}
				}
			}
		}
	}
}

/**
 * @brief  Display QSPI Demo Hint
 * @param  None
 * @retval None
 */
static void QSPI_SetHint(void)
{
	//	uint32_t x_size;
	//	uint32_t y_size;
	//	BSP_LCD_GetXSize(0, &x_size);
	//	BSP_LCD_GetYSize(0, &y_size);
	//	/* Clear the LCD */
	//	UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);
	//
	//	/* Set LCD Demo description */
	//	UTIL_LCD_FillRect(0, 0, x_size, 80,UTIL_LCD_COLOR_BLUE);
	//	UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
	//	UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
	//	UTIL_LCD_SetFont(&Font24);
	//	UTIL_LCD_DisplayStringAt(0, 0, (uint8_t*)"QSPI", CENTER_MODE);
	//	UTIL_LCD_SetFont(&Font12);
	//	UTIL_LCD_DisplayStringAt(0, 30, (uint8_t*)"This example shows how to write", CENTER_MODE);
	//	UTIL_LCD_DisplayStringAt(0, 45, (uint8_t*)"and read data on QSPI memory", CENTER_MODE);
	//	UTIL_LCD_DisplayStringAt(0, 60, (uint8_t*)"(Hardware modifications needed)", CENTER_MODE);
	//
	//	/* Set the LCD Text Color */
	//	UTIL_LCD_DrawRect(10, 90, x_size - 20,y_size- 100,UTIL_LCD_COLOR_BLUE);
	//	UTIL_LCD_DrawRect(11, 91, x_size - 22, y_size- 102,UTIL_LCD_COLOR_BLUE);
	//
	//	UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
	//	UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
}

/**
 * @brief  Fills buffer with user predefined data.
 * @param  pBuffer: pointer on the buffer to fill
 * @param  uwBufferLenght: size of the buffer to fill
 * @param  uwOffset: first value to fill on the buffer
 * @retval None
 */
static void Fill_Buffer(uint8_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
	uint32_t tmpIndex = 0;

	/* Put in global buffer different values */
	for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
	{
		pBuffer[tmpIndex] = tmpIndex + uwOffset;
	}
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param  BufferLength: buffer's length
 * @retval 1: pBuffer identical to pBuffer1
 *         0: pBuffer differs from pBuffer1
 */
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
	while (BufferLength--)
	{
		if (*pBuffer1 != *pBuffer2)
		{
			return 1;
		}

		pBuffer1++;
		pBuffer2++;
	}

	return 0;
}

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */

  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */

  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 3;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 1;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_ENABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */
	BSP_QSPI_Init_t init ;
	init.InterfaceMode=MT25TL01G_QPI_MODE;
	init.TransferRate= MT25TL01G_DTR_TRANSFER ;
	init.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
	if (BSP_QSPI_Init(0,&init) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	QSPI_CommandTypeDef      s_command;
	QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;
	/* Configure the command for the read instruction */
	s_command.InstructionMode   = QSPI_INSTRUCTION_4_LINES;
	s_command.Instruction       = MT25TL01G_QUAD_INOUT_FAST_READ_DTR_CMD; //QUAD_INOUT_FAST_READ_CMD;
	s_command.AddressMode       = QSPI_ADDRESS_4_LINES;
	s_command.AddressSize       = QSPI_ADDRESS_32_BITS;
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	s_command.DataMode          = QSPI_DATA_4_LINES;
	s_command.DummyCycles       = MT25TL01G_DUMMY_CYCLES_READ_QUAD_DTR; //N25Q128A_DUMMY_CYCLES_READ_QUAD;
	s_command.DdrMode           = QSPI_DDR_MODE_ENABLE;
	s_command.DdrHoldHalfCycle  = QSPI_DDR_HHC_HALF_CLK_DELAY;
	s_command.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	/* Configure the memory mapped mode */
	s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
	s_mem_mapped_cfg.TimeOutPeriod     = 0;

	if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg) != HAL_OK)
	{
		Error_Handler();
	}

	/* USER CODE BEGIN QUADSPI_Init 2 */

  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    */
    GPIO_InitStruct.Pin = QSPI_BK2_IO2_Pin|QSPI_BK2_IO3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_NCS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_NCS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO3_Pin|QSPI_BK1_IO2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_IO1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK2_IO0_Pin|QSPI_BK2_IO1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(QSPI_CLK_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_IO0_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    */
    HAL_GPIO_DeInit(GPIOG, QSPI_BK2_IO2_Pin|QSPI_BK2_IO3_Pin|QSPI_BK1_NCS_Pin);

    HAL_GPIO_DeInit(GPIOF, QSPI_BK1_IO3_Pin|QSPI_BK1_IO2_Pin|QSPI_BK1_IO1_Pin);

    HAL_GPIO_DeInit(GPIOH, QSPI_BK2_IO0_Pin|QSPI_BK2_IO1_Pin);

    HAL_GPIO_DeInit(QSPI_CLK_GPIO_Port, QSPI_CLK_Pin);

    HAL_GPIO_DeInit(QSPI_BK1_IO0_GPIO_Port, QSPI_BK1_IO0_Pin);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
