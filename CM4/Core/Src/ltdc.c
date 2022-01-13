/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */
extern DSI_HandleTypeDef hdsi;
OTM8009A_Object_t OTM8009AObj;
OTM8009A_IO_t IOCtx;
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 2;
  hltdc.Init.AccumulatedVBP = 2;
  hltdc.Init.AccumulatedActiveW = 402;
  hltdc.Init.AccumulatedActiveH = 482;
  hltdc.Init.TotalWidth = 403;
  hltdc.Init.TotalHeigh = 483;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 400;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0xD0000000;
  pLayerCfg.ImageWidth = 400;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

	      /* Configure DSI PHY HS2LP and LP2HS timings */

	  __HAL_LTDC_DISABLE(&hltdc);
	  DSI_LPCmdTypeDef LPCmd;

	  HAL_DSI_Start(&hdsi);

	  /* Configure the audio driver */
	  IOCtx.Address     = 0;
	  IOCtx.GetTick     = BSP_GetTick;
	  IOCtx.WriteReg    = DSI_IO_Write;
	  IOCtx.ReadReg     = DSI_IO_Read;
	  OTM8009A_RegisterBusIO(&OTM8009AObj, &IOCtx);

	  OTM8009A_Init(&OTM8009AObj ,OTM8009A_FORMAT_RGB888, OTM8009A_ORIENTATION_LANDSCAPE);
	  HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, OTM8009A_CMD_DISPOFF, 0x00);

	  LPCmd.LPGenShortWriteNoP = DSI_LP_GSW0P_DISABLE;
	  LPCmd.LPGenShortWriteOneP = DSI_LP_GSW1P_DISABLE;
	  LPCmd.LPGenShortWriteTwoP = DSI_LP_GSW2P_DISABLE;
	  LPCmd.LPGenShortReadNoP = DSI_LP_GSR0P_DISABLE;
	  LPCmd.LPGenShortReadOneP = DSI_LP_GSR1P_DISABLE;
	  LPCmd.LPGenShortReadTwoP = DSI_LP_GSR2P_DISABLE;
	  LPCmd.LPGenLongWrite = DSI_LP_GLW_DISABLE;
	  LPCmd.LPDcsShortWriteNoP = DSI_LP_DSW0P_DISABLE;
	  LPCmd.LPDcsShortWriteOneP = DSI_LP_DSW1P_DISABLE;
	  LPCmd.LPDcsShortReadNoP = DSI_LP_DSR0P_DISABLE;
	  LPCmd.LPDcsLongWrite = DSI_LP_DLW_DISABLE;
	  HAL_DSI_ConfigCommand(&hdsi, &LPCmd);

	  HAL_LTDC_SetPitch(&hltdc, 800, 0);
	  __HAL_LTDC_ENABLE(&hltdc);
  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */
  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 5;
    PeriphClkInitStruct.PLL3.PLL3N = 161;
    PeriphClkInitStruct.PLL3.PLL3P = 4;
    PeriphClkInitStruct.PLL3.PLL3Q = 4;
    PeriphClkInitStruct.PLL3.PLL3R = 21;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
