/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA2D_HandleTypeDef hdma2d;
extern DSI_HandleTypeDef hdsi;
extern LTDC_HandleTypeDef hltdc;
extern TIM_HandleTypeDef htim3;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
//  HAL_RCC_NMI_IRQHandler();
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles LTDC global interrupt.
  */
void LTDC_IRQHandler(void)
{
  /* USER CODE BEGIN LTDC_IRQn 0 */

  /* USER CODE END LTDC_IRQn 0 */
  HAL_LTDC_IRQHandler(&hltdc);
  /* USER CODE BEGIN LTDC_IRQn 1 */

  /* USER CODE END LTDC_IRQn 1 */
}

/**
  * @brief This function handles DMA2D global interrupt.
  */
void DMA2D_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2D_IRQn 0 */

  /* USER CODE END DMA2D_IRQn 0 */
  HAL_DMA2D_IRQHandler(&hdma2d);
  /* USER CODE BEGIN DMA2D_IRQn 1 */

  /* USER CODE END DMA2D_IRQn 1 */
}

/**
  * @brief This function handles DSI global Interrupt.
  */
void DSI_IRQHandler(void)
{
  /* USER CODE BEGIN DSI_IRQn 0 */

  /* USER CODE END DSI_IRQn 0 */
  HAL_DSI_IRQHandler(&hdsi);
  /* USER CODE BEGIN DSI_IRQn 1 */

  /* USER CODE END DSI_IRQn 1 */
}

void WWDG_IRQHandler(void) {}
void PVD_AVD_IRQHandler(void) {}
void TAMP_STAMP_IRQHandler(void) {}
void RTC_WKUP_IRQHandler(void) {}
void FLASH_IRQHandler(void) {}
void RCC_IRQHandler(void) {}
void EXTI0_IRQHandler(void) {}
void EXTI1_IRQHandler(void) {}
void EXTI2_IRQHandler(void) {}
void EXTI3_IRQHandler(void) {}
void EXTI4_IRQHandler(void) {}
void DMA1_Stream0_IRQHandler(void) {}
void DMA1_Stream1_IRQHandler(void) {}
void DMA1_Stream2_IRQHandler(void) {}
void DMA1_Stream3_IRQHandler(void) {}
void DMA1_Stream4_IRQHandler(void) {}
void DMA1_Stream5_IRQHandler(void) {}
void DMA1_Stream6_IRQHandler(void) {}
void ADC_IRQHandler(void) {}
void FDCAN1_IT0_IRQHandler(void) {}
void FDCAN2_IT0_IRQHandler(void) {}
void FDCAN1_IT1_IRQHandler(void) {}
void FDCAN2_IT1_IRQHandler(void) {}
void EXTI9_5_IRQHandler(void) {}
void TIM1_BRK_IRQHandler(void) {}
void TIM1_UP_IRQHandler(void) {}
void TIM1_TRG_COM_IRQHandler(void) {}
void TIM1_CC_IRQHandler(void) {}
void TIM2_IRQHandler(void) {}
void TIM4_IRQHandler(void) {}
void I2C1_EV_IRQHandler(void) {}
void I2C1_ER_IRQHandler(void) {}
void I2C2_EV_IRQHandler(void) {}
void I2C2_ER_IRQHandler(void) {}
void SPI1_IRQHandler(void) {}
void SPI2_IRQHandler(void) {}
void USART1_IRQHandler(void) {}
void USART2_IRQHandler(void) {}
void USART3_IRQHandler(void) {}
void EXTI15_10_IRQHandler(void) {}
void RTC_Alarm_IRQHandler(void) {}
void TIM8_BRK_TIM12_IRQHandler(void) {}
void TIM8_UP_TIM13_IRQHandler(void) {}
void TIM8_TRG_COM_TIM14_IRQHandler(void) {}
void TIM8_CC_IRQHandler(void) {}
void DMA1_Stream7_IRQHandler(void) {}
void FMC_IRQHandler(void) {}
void SDMMC1_IRQHandler(void) {}
void TIM5_IRQHandler(void) {}
void SPI3_IRQHandler(void) {}
void UART4_IRQHandler(void) {}
void UART5_IRQHandler(void) {}
void TIM6_DAC_IRQHandler(void) {}
void TIM7_IRQHandler(void) {}
void DMA2_Stream0_IRQHandler(void) {}
void DMA2_Stream1_IRQHandler(void) {}
void DMA2_Stream2_IRQHandler(void) {}
void DMA2_Stream3_IRQHandler(void) {}
void DMA2_Stream4_IRQHandler(void) {}
void ETH_IRQHandler(void) {}
void ETH_WKUP_IRQHandler(void) {}
void FDCAN_CAL_IRQHandler(void) {}
void CM7_SEV_IRQHandler(void) {}
void CM4_SEV_IRQHandler(void) {}
void DMA2_Stream5_IRQHandler(void) {}
void DMA2_Stream6_IRQHandler(void) {}
void DMA2_Stream7_IRQHandler(void) {}
void USART6_IRQHandler(void) {}
void I2C3_EV_IRQHandler(void) {}
void I2C3_ER_IRQHandler(void) {}
void OTG_HS_EP1_OUT_IRQHandler(void) {}
void OTG_HS_EP1_IN_IRQHandler(void) {}
void OTG_HS_WKUP_IRQHandler(void) {}
void OTG_HS_IRQHandler(void) {}
void DCMI_IRQHandler(void) {}
void RNG_IRQHandler(void) {}
void FPU_IRQHandler(void) {}
void UART7_IRQHandler(void) {}
void UART8_IRQHandler(void) {}
void SPI4_IRQHandler(void) {}
void SPI5_IRQHandler(void) {}
void SPI6_IRQHandler(void) {}
void SAI1_IRQHandler(void) {}
void LTDC_ER_IRQHandler(void) {}
void SAI2_IRQHandler(void) {}
void QUADSPI_IRQHandler(void) {}
void LPTIM1_IRQHandler(void) {}
void CEC_IRQHandler(void) {}
void I2C4_EV_IRQHandler(void) {}
void I2C4_ER_IRQHandler(void) {}
void SPDIF_RX_IRQHandler(void) {}
void OTG_FS_EP1_OUT_IRQHandler(void) {}
void OTG_FS_EP1_IN_IRQHandler(void) {}
void OTG_FS_WKUP_IRQHandler(void) {}
void OTG_FS_IRQHandler(void) {}
void DMAMUX1_OVR_IRQHandler(void) {}
void HRTIM1_Master_IRQHandler(void) {}
void HRTIM1_TIMA_IRQHandler(void) {}
void HRTIM1_TIMB_IRQHandler(void) {}
void HRTIM1_TIMC_IRQHandler(void) {}
void HRTIM1_TIMD_IRQHandler(void) {}
void HRTIM1_TIME_IRQHandler(void) {}
void HRTIM1_FLT_IRQHandler(void) {}
void DFSDM1_FLT0_IRQHandler(void) {}
void DFSDM1_FLT1_IRQHandler(void) {}
void DFSDM1_FLT2_IRQHandler(void) {}
void DFSDM1_FLT3_IRQHandler(void) {}
void SAI3_IRQHandler(void) {}
void SWPMI1_IRQHandler(void) {}
void TIM15_IRQHandler(void) {}
void TIM16_IRQHandler(void) {}
void TIM17_IRQHandler(void) {}
void MDIOS_WKUP_IRQHandler(void) {}
void MDIOS_IRQHandler(void) {}
void JPEG_IRQHandler(void) {}
void MDMA_IRQHandler(void) {}
void SDMMC2_IRQHandler(void) {}
void HSEM1_IRQHandler(void) {}
void HSEM2_IRQHandler(void) {}
void ADC3_IRQHandler(void) {}
void DMAMUX2_OVR_IRQHandler(void) {}
void BDMA_Channel0_IRQHandler(void) {}
void BDMA_Channel1_IRQHandler(void) {}
void BDMA_Channel2_IRQHandler(void) {}
void BDMA_Channel3_IRQHandler(void) {}
void BDMA_Channel4_IRQHandler(void) {}
void BDMA_Channel5_IRQHandler(void) {}
void BDMA_Channel6_IRQHandler(void) {}
void BDMA_Channel7_IRQHandler(void) {}
void COMP1_IRQHandler(void) {}
void LPTIM2_IRQHandler(void) {}
void LPTIM3_IRQHandler(void) {}
void LPTIM4_IRQHandler(void) {}
void LPTIM5_IRQHandler(void) {}
void LPUART1_IRQHandler(void) {}
void WWDG_RST_IRQHandler(void) {}
void CRS_IRQHandler(void) {}
void ECC_IRQHandler(void) {}
void SAI4_IRQHandler(void) {}
void HOLD_CORE_IRQHandler(void) {}
void WAKEUP_PIN_IRQHandler(void) {}
void PendSV_Handler(void) {}

/* USER CODE BEGIN 1 */
///**
//  * @brief  Handles MDMA transfer interrupt request.
//  * @retval None
//  */
//void MDMA_IRQHandler(void)
//{
//    BSP_SDRAM_IRQHandler(0);
//}
//
///**
//* @brief  This function handles External line 2 interrupt request.
//* @param  None
//* @retval None
//*/
//void EXTI2_IRQHandler(void)
//{
//   BSP_JOY_IRQHandler(JOY1, JOY_SEL);
//}
//
///**
//* @brief  This function handles External line 3 interrupt request.
//* @param  None
//* @retval None
//*/
//void EXTI3_IRQHandler(void)
//{
//   BSP_JOY_IRQHandler(JOY1, JOY_DOWN);
//}
//
///**
//* @brief  This function handles External line 4 interrupt request.
//* @param  None
//* @retval None
//*/
//void EXTI4_IRQHandler(void)
//{
//   BSP_JOY_IRQHandler(JOY1, JOY_LEFT);
//}
//
///**
//* @brief  This function handles External lines 9 to 5 interrupt request.
//* @param  None
//* @retval None
//*/
//void EXTI9_5_IRQHandler(void)
//{
//  BSP_JOY_IRQHandler(JOY1, JOY_RIGHT);
//  BSP_JOY_IRQHandler(JOY1, JOY_UP);
//}
//
///**
//  * @brief  This function handles External lines 15 to 10 interrupt request.
//  * @param  None
//  * @retval None
//  */
//void EXTI15_10_IRQHandler(void)
//{
//  BSP_PB_IRQHandler(BUTTON_WAKEUP);
//}
/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
