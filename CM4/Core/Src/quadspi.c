/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.c
  * @brief   This file provides code for the configuration
  *          of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "quadspi.h"

/* USER CODE BEGIN 0 */
#include "main.h"
#include "config.h"
#include "shared.h"
#include "basetypes.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void QSPI_memoryMappedToIndirect(void);
static void QSPI_indirectToMemoryMapped(void);
static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

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

/**
 * @brief  Switch from memory mapped QSPI acces mode to indirect mode
 * @param  void
 * @retval void
 */
static void QSPI_memoryMappedToIndirect(void)
{
	HAL_QSPI_DeInit(&hqspi);
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

	//    if (BSP_QSPI_DisableMemoryMappedMode(0) != BSP_ERROR_NONE)
	//    {
	//        Error_Handler();
	//    }

	//    BSP_QSPI_DeInit(0);

	BSP_QSPI_Init_t init;
	init.InterfaceMode = MT25TL01G_QPI_MODE;
	init.TransferRate = MT25TL01G_DTR_TRANSFER;
	init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;

	extern BSP_QSPI_Ctx_t QSPI_Ctx[QSPI_INSTANCES_NUMBER];
	QSPI_Ctx[0].IsInitialized = QSPI_ACCESS_NONE;

	if (BSP_QSPI_Init(0, &init) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}
}

/**
 * @brief  Switch from indirect QSPI acces to memory mapped mode
 * @param  void
 * @retval void
 */
static void QSPI_indirectToMemoryMapped(void)
{
	HAL_QSPI_DeInit(&hqspi);
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

	//	BSP_QSPI_DeInit(0);

	BSP_QSPI_Init_t init;
	init.InterfaceMode = MT25TL01G_QPI_MODE;
	init.TransferRate = MT25TL01G_DTR_TRANSFER;
	init.DualFlashMode = MT25TL01G_DUALFLASH_ENABLE;

	extern BSP_QSPI_Ctx_t QSPI_Ctx[QSPI_INSTANCES_NUMBER];
	QSPI_Ctx[0].IsInitialized = QSPI_ACCESS_NONE;

	if (BSP_QSPI_Init(0, &init) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}
	if (BSP_QSPI_EnableMemoryMappedMode(0) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}
	HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
}

/**
 * @brief  QSPI reset flash data at config.h values
 * @param  void
 * @retval void
 */
void QSPI_ResetData(void)
{
	uint8_t qspi_aTxBuffer[BUFFER_SIZE];
	uint8_t qspi_aRxBuffer[BUFFER_SIZE];
	uint8_t isFlashInitialized = TRUE;

	struct flashParms *tmp_Txflash_params = (struct flashParms *)qspi_aTxBuffer;
	struct flashParms *tmp_Rxflash_params = (struct flashParms *)qspi_aRxBuffer;

	QSPI_memoryMappedToIndirect();

	/* Read back data from the QSPI memory */
	if(BSP_QSPI_Read(0,qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	if (tmp_Rxflash_params->params.start_frequency == 0)
	{
		tmp_Txflash_params->params.start_frequency = START_FREQUENCY;
		isFlashInitialized = FALSE;
	}
	if (tmp_Rxflash_params->params.comma_per_semitone == 0)
	{
		tmp_Txflash_params->params.comma_per_semitone = COMMA_PER_SEMITONE;
		isFlashInitialized = FALSE;
	}
	if (tmp_Rxflash_params->params.ifft_attack == 0)
	{
		tmp_Txflash_params->params.ifft_attack = IFFT_GAP_PER_LOOP_INCREASE;
		isFlashInitialized = FALSE;
	}
	if (tmp_Rxflash_params->params.ifft_release == 0)
	{
		tmp_Txflash_params->params.ifft_release = IFFT_GAP_PER_LOOP_DECREASE;
		isFlashInitialized = FALSE;
	}
	if (tmp_Rxflash_params->params.volume == 0)
	{
		tmp_Txflash_params->params.volume = VOLUME;
		isFlashInitialized = FALSE;
	}

	if (isFlashInitialized == TRUE)
	{
		QSPI_indirectToMemoryMapped();
		return;
	}

	/* Erase QSPI memory */
	if(BSP_QSPI_EraseBlock(0,WRITE_READ_ADDR,BSP_QSPI_ERASE_8K) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	if(BSP_QSPI_Write(0,qspi_aTxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	/* Read back data from the QSPI memory */
	if(BSP_QSPI_Read(0,qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	/* Checking data integrity */
	if(Buffercmp(qspi_aRxBuffer, qspi_aTxBuffer, BUFFER_SIZE) > 0)
	{
		Error_Handler();
	}

	QSPI_indirectToMemoryMapped();
}

/**
 * @brief  QSPI initialize flash data at config.h values
 * @param  void
 * @retval void
 */
void QSPI_InitSharedData(void)
{
	uint8_t qspi_aRxBuffer[BUFFER_SIZE];

	struct flashParms *tmp_Rxflash_params = (struct flashParms *)qspi_aRxBuffer;

	QSPI_memoryMappedToIndirect();

	/* Read back data from the QSPI memory */
	if(BSP_QSPI_Read(0,qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	params.start_frequency 			= tmp_Rxflash_params->params.start_frequency;
	params.comma_per_semitone		= tmp_Rxflash_params->params.comma_per_semitone;
	params.ifft_attack				= tmp_Rxflash_params->params.ifft_attack;
	params.ifft_release				= tmp_Rxflash_params->params.ifft_release;
	params.volume					= tmp_Rxflash_params->params.volume;
	guiValues.attackSlider			= tmp_Rxflash_params->guiValues.attackSlider;
	guiValues.releaseSlider			= tmp_Rxflash_params->guiValues.releaseSlider;

	QSPI_indirectToMemoryMapped();
}

/**
 * @brief  QSPI update flash data with shared RAM values
 * @param  void
 * @retval void
 */
void QSPI_UpdateData(void)
{
	uint8_t qspi_aTxBuffer[BUFFER_SIZE];
	uint8_t qspi_aRxBuffer[BUFFER_SIZE];

	struct flashParms *tmp_Txflash_params = (struct flashParms *)qspi_aTxBuffer;

	QSPI_memoryMappedToIndirect();

	tmp_Txflash_params->params.start_frequency = START_FREQUENCY;
	tmp_Txflash_params->params.comma_per_semitone = COMMA_PER_SEMITONE;
	tmp_Txflash_params->params.ifft_attack = params.ifft_attack;
	tmp_Txflash_params->params.ifft_release = params.ifft_release;
	tmp_Txflash_params->params.volume = VOLUME;
	tmp_Txflash_params->guiValues.attackSlider = guiValues.attackSlider;
	tmp_Txflash_params->guiValues.releaseSlider = guiValues.releaseSlider;

	/* Erase QSPI memory */
	if(BSP_QSPI_EraseBlock(0,WRITE_READ_ADDR,BSP_QSPI_ERASE_8K) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	if(BSP_QSPI_Write(0,qspi_aTxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	/* Read back data from the QSPI memory */
	if(BSP_QSPI_Read(0,qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != BSP_ERROR_NONE)
	{
		Error_Handler();
	}

	/* Checking data integrity */
	if(Buffercmp(qspi_aRxBuffer, qspi_aTxBuffer, BUFFER_SIZE) > 0)
	{
		Error_Handler();
	}

	QSPI_indirectToMemoryMapped();
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

	if (BSP_QSPI_EnableMemoryMappedMode(0) != BSP_ERROR_NONE)
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
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_NCS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_NCS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO3_Pin|QSPI_BK1_IO2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(QSPI_BK1_IO1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK2_IO0_Pin|QSPI_BK2_IO1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(QSPI_CLK_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = QSPI_BK1_IO0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
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
