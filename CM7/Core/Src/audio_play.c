/**
  ******************************************************************************
  * @file    BSP/CM7/Src/audio_play.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the audio feature in the
  *          stm32747i_discovery driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

/** @addtogroup STM32H7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/*Since SysTick is set to 1ms (unless to set it quicker) */
/* to run up to 48khz, a buffer around 1000 (or more) is requested*/
/* to run up to 96khz, a buffer around 2000 (or more) is requested*/
#define AUDIO_DEFAULT_VOLUME    70

/* Audio file size and start address are defined here since the audio file is
   stored in Flash memory as a constant table of 16-bit data */
#define AUDIO_START_OFFSET_ADDRESS    0            /* Offset relative to audio file header size */
#define AUDIO_BUFFER_SIZE            2048

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_INIT,
  AUDIO_STATE_PLAYING,
  AUDIO_STATE_PAUSE
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

typedef struct {
  uint8_t buff[AUDIO_BUFFER_SIZE];
  uint32_t fptr;
  BUFFER_StateTypeDef state;
  uint32_t AudioFileSize;
  uint32_t *SrcAddress;
}AUDIO_BufferTypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ALIGN_32BYTES (static AUDIO_BufferTypeDef  buffer_ctl);
static AUDIO_PLAYBACK_StateTypeDef  audio_state;
__IO uint32_t uwVolume = 20;
__IO uint32_t uwPauseEnabledStatus = 0;
uint32_t bytesread;

static uint32_t AudioFreq[9] ={8000 , 11025, 16000, 22050, 32000, 44100, 48000, 96000, 192000};
uint32_t JoyState;
BSP_AUDIO_Init_t* AudioPlayInit;
/* Private function prototypes -----------------------------------------------*/
static void Audio_SetHint(void);
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData);
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size);
AUDIO_ErrorTypeDef AUDIO_Stop(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Audio Play demo
  * @param  None
  * @retval None
  */
void AudioPlay_demo (void)
{
  uint32_t x_size, y_size;
  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
  uint8_t status = 0;
  uint32_t *AudioFreq_ptr;
  AudioFreq_ptr = AudioFreq+6; /*AF_48K*/
  uint8_t FreqStr[256] = {0};

  uwVolume = 40;

  Audio_SetHint();

  status =  BSP_JOY_Init(JOY1, JOY_MODE_EXTI, JOY_ALL);

  if (status != HAL_OK)
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_DisplayStringAt(0, x_size - 115, (uint8_t *)"ERROR", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, x_size - 100, (uint8_t *)"Joystick cannot be initialized", CENTER_MODE);
  }
  AudioPlayInit->Device = AUDIO_OUT_DEVICE_HEADPHONE;
  AudioPlayInit->ChannelsNbr = 2;
  AudioPlayInit->SampleRate = 96000 ;
  AudioPlayInit->BitsPerSample = AUDIO_RESOLUTION_16B;
  AudioPlayInit->Volume = uwVolume;
  if(BSP_AUDIO_OUT_Init(0, AudioPlayInit) == 0)
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_GREEN);
    UTIL_LCD_DisplayStringAt(0, x_size - 115, (uint8_t *)"  AUDIO CODEC   OK  ", CENTER_MODE);
  }
  else
  {
    UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
    UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
    UTIL_LCD_DisplayStringAt(0, x_size - 115, (uint8_t *)"  AUDIO CODEC  FAIL ", CENTER_MODE);
    UTIL_LCD_DisplayStringAt(0, x_size - 100, (uint8_t *)" Try to reset board ", CENTER_MODE);
  }

  /*
  Start playing the file from a circular buffer, once the DMA is enabled, it is
  always in running state. Application has to fill the buffer with the audio data
  using Transfer complete and/or half transfer complete interrupts callbacks
  (AUDIO_TransferComplete_CallBack() or AUDIO_HalfTransfer_CallBack()...
  */
  AUDIO_Start((uint32_t *)AUDIO_SRC_FILE_ADDRESS, (uint32_t)AUDIO_FILE_SIZE);

  /* Display the state on the screen */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DisplayStringAt(0, x_size - 80, (uint8_t *)"       PLAYING...     ", CENTER_MODE);

  sprintf((char*)FreqStr, "       VOL:    %3lu     ", uwVolume);
  UTIL_LCD_DisplayStringAt(0, x_size - 65, (uint8_t *)FreqStr, CENTER_MODE);

  sprintf((char*)FreqStr, "      FREQ: %6lu     ", *AudioFreq_ptr);
  UTIL_LCD_DisplayStringAt(0, x_size - 50, (uint8_t *)FreqStr, CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, LINE(15), (uint8_t *)"Hear nothing ?", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, LINE(16), (uint8_t *)"Have you copied the audio file with STM-LINK UTILITY ?", CENTER_MODE);

  /* Infinite loop */
  while (1)
  {
    AUDIO_Process();
    switch (JoyState)
    {
      case JOY_UP:
        if (audio_state != AUDIO_STATE_PAUSE)
        {
          /* Increase volume by 5% */
          if (uwVolume < 95)
            uwVolume += 5;
          else
            uwVolume = 100;
          sprintf((char*)FreqStr, "       VOL:    %3lu     ", uwVolume);
          BSP_AUDIO_OUT_SetVolume(0,uwVolume);
          UTIL_LCD_DisplayStringAt(0, x_size - 65, (uint8_t *)FreqStr, CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"                      ", CENTER_MODE);
          HAL_Delay(100);
        }
        break;
      case JOY_DOWN:
        if (audio_state != AUDIO_STATE_PAUSE)
        {
          /* Decrease volume by 5% */
          if (uwVolume > 5)
            uwVolume -= 5;
          else
            uwVolume = 0;
          sprintf((char*)FreqStr, "       VOL:    %3lu     ", uwVolume);
          BSP_AUDIO_OUT_SetVolume(0,uwVolume);
          UTIL_LCD_DisplayStringAt(0, x_size - 65, (uint8_t *)FreqStr, CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"                      ", CENTER_MODE);
          HAL_Delay(100);
        }
        break;
      case JOY_LEFT:
        if (audio_state != AUDIO_STATE_PAUSE)
        {
          /*Decrease Frequency */
          if (*AudioFreq_ptr != 8000)
          {
            AudioFreq_ptr--;
            sprintf((char*)FreqStr, "      FREQ: %6lu     ", *AudioFreq_ptr);
            BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
            AudioPlayInit->Device = AUDIO_OUT_DEVICE_SPK_HP;
            AudioPlayInit->ChannelsNbr = 2;
            AudioPlayInit->SampleRate = *AudioFreq_ptr;
            AudioPlayInit->BitsPerSample = AUDIO_RESOLUTION_16B;
            AudioPlayInit->Volume = uwVolume;
            BSP_AUDIO_OUT_Init(0,AudioPlayInit);
            AUDIO_Start((uint32_t *)AUDIO_SRC_FILE_ADDRESS, (uint32_t)AUDIO_FILE_SIZE);
            BSP_AUDIO_OUT_SetVolume(0,uwVolume);
          }
          UTIL_LCD_DisplayStringAt(0, x_size - 50, (uint8_t *)FreqStr, CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"                      ", CENTER_MODE);
          HAL_Delay(100);
        }
        break;
      case JOY_RIGHT:
        if (audio_state != AUDIO_STATE_PAUSE)
        {
          /* Increase Frequency */
          if (*AudioFreq_ptr != 96000)
          {
            AudioFreq_ptr++;
            sprintf((char*)FreqStr, "      FREQ: %6lu     ", *AudioFreq_ptr);
            BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
            AudioPlayInit->Device = AUDIO_OUT_DEVICE_SPK_HP;
            AudioPlayInit->ChannelsNbr = 2;
            AudioPlayInit->SampleRate = *AudioFreq_ptr;
            AudioPlayInit->BitsPerSample = AUDIO_RESOLUTION_16B;
            AudioPlayInit->Volume = uwVolume;
            BSP_AUDIO_OUT_Init(0,AudioPlayInit);
            AUDIO_Start((uint32_t *)AUDIO_SRC_FILE_ADDRESS, (uint32_t)AUDIO_FILE_SIZE);
            BSP_AUDIO_OUT_SetVolume(0,uwVolume);
          }

          UTIL_LCD_DisplayStringAt(0, x_size - 50, (uint8_t *)FreqStr, CENTER_MODE);
          UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"                      ", CENTER_MODE);
          HAL_Delay(100);
        }
        break;
      case JOY_SEL:
        /* Set Pause / Resume */
        if (audio_state == AUDIO_STATE_PAUSE)
        {
          /* Pause is enabled, call Resume */
          BSP_AUDIO_OUT_Resume(0);
          audio_state = AUDIO_STATE_PLAYING;
          UTIL_LCD_DisplayStringAt(0, x_size - 80, (uint8_t *)"       PLAYING...     ", CENTER_MODE);
        }
        else
        {
          /* Pause the playback */
          BSP_AUDIO_OUT_Pause(0);
          audio_state = AUDIO_STATE_PAUSE;
          UTIL_LCD_DisplayStringAt(0, x_size - 80, (uint8_t *)"       PAUSE  ...     ", CENTER_MODE);
        }
        UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"                      ", CENTER_MODE);
        HAL_Delay(200);
        break;

      default:
        break;
    }

    if (CheckForUserInput() > 0)
    {
      /* Stop Player before close Test */
      BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
      BSP_AUDIO_OUT_DeInit(0);
      return;
    }
  }
}

/**
  * @brief  Display Audio demo hint
  * @param  None
  * @retval None
  */
static void Audio_SetHint(void)
{
  uint32_t x_size, y_size;
  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
  /* Clear the LCD */
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  /* Set Audio Demo description */

  UTIL_LCD_FillRect(0, 0, x_size, 95, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetFont(&Font24);
  UTIL_LCD_DisplayStringAt(0, 0, (uint8_t *)"AUDIO EXAMPLE", CENTER_MODE);
  UTIL_LCD_SetFont(&Font16);
  UTIL_LCD_DisplayStringAt(0, 30, (uint8_t *)"Press Tamper button for next menu          ", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 45, (uint8_t *)"Use Joystick Up/Down    to change Volume   ", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 60, (uint8_t *)"Use Joystick Left/Right to change Frequency", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 75, (uint8_t *)"Click on Joystick for Pause/Resume         ", CENTER_MODE);


  UTIL_LCD_DrawRect(10, 105, x_size - 20, y_size - 110, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DrawRect(11, 106, x_size - 22, y_size - 112, UTIL_LCD_COLOR_BLUE);

}


/**
  * @brief  Starts Audio streaming.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size)
{
  uint32_t bytesread;

  buffer_ctl.state = BUFFER_OFFSET_NONE;
  buffer_ctl.AudioFileSize = file_size;
  buffer_ctl.SrcAddress = psrc_address;

  bytesread = GetData( (void *)psrc_address,
                       0,
                       &buffer_ctl.buff[0],
                       AUDIO_BUFFER_SIZE);
  if(bytesread > 0)
  {
    BSP_AUDIO_OUT_Play(0,(uint8_t *)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE);
    audio_state = AUDIO_STATE_PLAYING;
    buffer_ctl.fptr = bytesread;
    return AUDIO_ERROR_NONE;
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process.
  * @param  None
  * @retval Audio error
  */
uint8_t AUDIO_Process(void)
{
  uint32_t bytesread;
  AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;

  switch(audio_state)
  {
  case AUDIO_STATE_PLAYING:

    if(buffer_ctl.fptr >= buffer_ctl.AudioFileSize)
    {
      /* Play audio sample again ... */
      buffer_ctl.fptr = 0;
      error_state = AUDIO_ERROR_EOF;
    }

    /* 1st half buffer played; so fill it and continue playing from bottom*/
    if(buffer_ctl.state == BUFFER_OFFSET_HALF)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[0],
                          AUDIO_BUFFER_SIZE /2);

      if( bytesread >0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
              /* Clean Data Cache to update the content of the SRAM */
      SCB_CleanDCache_by_Addr((uint32_t*)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE/2);
      }
    }

    /* 2nd half buffer played; so fill it and continue playing from top */
    if(buffer_ctl.state == BUFFER_OFFSET_FULL)
    {
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[AUDIO_BUFFER_SIZE /2],
                          AUDIO_BUFFER_SIZE /2);
      if( bytesread > 0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
        buffer_ctl.fptr += bytesread;
      /* Clean Data Cache to update the content of the SRAM */
      SCB_CleanDCache_by_Addr((uint32_t*)&buffer_ctl.buff[AUDIO_BUFFER_SIZE/2], AUDIO_BUFFER_SIZE/2);
      }
    }
    break;

  default:
    error_state = AUDIO_ERROR_NOTREADY;
    break;
  }
  return (uint8_t) error_state;
}

/**
  * @brief  Gets Data from storage unit.
  * @param  None
  * @retval None
  */
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData)
{
  uint8_t *lptr = pdata;
  uint32_t ReadDataNbr;

  ReadDataNbr = 0;
  while(((offset + ReadDataNbr) < buffer_ctl.AudioFileSize) && (ReadDataNbr < NbrOfData))
  {
    pbuf[ReadDataNbr]= lptr [offset + ReadDataNbr];
    ReadDataNbr++;
  }
  return ReadDataNbr;
}

/*------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32h747i_discovery_audio.c file
           and their implementation should be done the user code if they are needed.
           Below some examples of callback implementations.
  ----------------------------------------------------------------------------*/
/**
  * @brief  Manages the full Transfer complete event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{
    if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 2nd part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
    if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 1st part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_HALF;
  }

}

/**
  * @brief  Manages the DMA FIFO error event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance)
{
  /* Display message on the LCD screen */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_RED);
  UTIL_LCD_DisplayStringAt(0, LINE(14), (uint8_t *)"       DMA  ERROR     ", CENTER_MODE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);

  /* Stop the program with an infinite loop */
  while (BSP_PB_GetState(BUTTON_WAKEUP) != RESET)
  {
    return;
  }

  /* could also generate a system reset to recover from the error */
  /* .... */
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
