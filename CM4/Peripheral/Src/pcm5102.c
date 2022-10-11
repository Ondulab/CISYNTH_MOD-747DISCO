/**
 ******************************************************************************
 * @file           : pcm5102.c
 * @brief          : Audio Stereo DAC with 32-bit, 384kHz PCM Interface
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"

#include "main.h"
#include "config.h"
#include "shared.h"

/* Private includes ----------------------------------------------------------*/
#include "pcm5102.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
BSP_AUDIO_Init_t AudioPlayInit;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  Initialise audio peripheral
 * @param  void
 * @retval void
 */
void pcm5102_Init(void)
{
	printf("----------- DAC INIT ----------\n");
	printf("-------------------------------\n");

	AudioPlayInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
	AudioPlayInit.ChannelsNbr = 2;
	AudioPlayInit.SampleRate = 48000 ;
	AudioPlayInit.BitsPerSample = AUDIO_RESOLUTION_32B;
	AudioPlayInit.Volume = VOLUME;
	if(BSP_AUDIO_OUT_Init(0, &AudioPlayInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief  Mute
 * @param  void
 * @retval void
 */
void pcm5102_Mute(void)
{
	BSP_AUDIO_OUT_Mute(0);
}

/**
 * @brief  Unmute
 * @param  void
 * @retval void
 */
void pcm5102_UnMute(void)
{

	BSP_AUDIO_OUT_UnMute(0);
}

/**
 * @brief  Get audio buffer data
 * @param  Index
 * @retval Value
 */
int32_t pcm5102_GetAudioData(uint32_t index)
{
	//	if (index >= RFFT_BUFFER_SIZE)
	//		Error_Handler();
	return audioBuff[index];
}

/**
 * @brief  Get audio buffer index pointer
 * @param  index
 * @retval index address
 */
volatile int32_t * pcm5102_GetDataPtr(uint32_t index)
{
	return &audioBuff[index];
}
