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

/* Private includes ----------------------------------------------------------*/
#include "pcm5102.h"

/* Private typedef -----------------------------------------------------------*/
static BUFFER_AUDIO_StateTypeDef bufferAudioState;

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static int16_t audioBuff[AUDIO_BUFFER_SIZE * 4] = {0};
//ALIGN_32BYTES (static AUDIO_BufferTypeDef  buffer_ctl) = {0};

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	AUDIO_STATE_IDLE = 0,
	AUDIO_STATE_INIT,
	AUDIO_STATE_PLAYING,
	AUDIO_STATE_PAUSE
}AUDIO_PLAYBACK_StateTypeDef;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/;
__IO uint32_t uwVolume = 90;
__IO uint32_t uwPauseEnabledStatus = 0;
uint32_t bytesread;

BSP_AUDIO_Init_t* AudioPlayInit;

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

	uwVolume = 80;

	AudioPlayInit->Device = AUDIO_OUT_DEVICE_HEADPHONE;
	AudioPlayInit->ChannelsNbr = 2;
	AudioPlayInit->SampleRate = 48000 ;
	AudioPlayInit->BitsPerSample = AUDIO_RESOLUTION_16B;
	AudioPlayInit->Volume = uwVolume;
	if(BSP_AUDIO_OUT_Init(0, AudioPlayInit) != HAL_OK)
	{
		Error_Handler();
	}

	bufferAudioState = AUDIO_BUFFER_OFFSET_NONE;
	HAL_SAI_Transmit_DMA(&haudio_out_sai,(uint8_t *)&audioBuff[0], AUDIO_BUFFER_SIZE * 4);
}

/**
 * @brief  Get audio buffer data
 * @param  Index
 * @retval Value
 */
int16_t pcm5102_GetAudioData(uint32_t index)
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
int16_t * pcm5102_GetDataPtr(uint32_t index)
{
	return &audioBuff[index];
}

/**
 * @brief  Get state of audio process
 * @param  void
 * @retval state
 */
__inline BUFFER_AUDIO_StateTypeDef * pcm5102_GetBufferState(void)
{
	return &bufferAudioState;
}

/**
 * @brief  Reset state of audio process
 * @param  void
 * @retval void
 */
__inline void pcm5102_ResetBufferState(void)
{
	bufferAudioState = AUDIO_BUFFER_OFFSET_NONE;
}

/*------------------------------------------------------------------------------
       Callbacks implementation:
           the callbacks API are defined __weak in the stm32769i_discovery_audio.c file
           and their implementation should be done the user code if they are needed.
           Below some examples of callback implementations.
  ----------------------------------------------------------------------------*/
/**
 * @brief  Manages the full Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Interface)
{
	/* allows AUDIO_Process() to refill 2nd part of the buffer  */
	bufferAudioState = AUDIO_BUFFER_OFFSET_FULL;
}

/**
 * @brief  Manages the DMA Half Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Interface)
{
	//	buffer_ctl.state = AUDIO_BUFFER_OFFSET_HALF;
	bufferAudioState = AUDIO_BUFFER_OFFSET_HALF;
}

/**
 * @brief  Manages the DMA FIFO error event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Interface)
{
	Error_Handler();
}
