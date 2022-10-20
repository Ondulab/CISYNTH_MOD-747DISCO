/**
 ******************************************************************************
 * @file           : pcm5102.h
 * @brief          : Audio Stereo DAC with 32-bit, 384kHz PCM Interface
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_H__
#define __AUDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "config.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void audio_Init(void);
void audio_Mute(void);
void audio_UnMute(void);
int32_t audio_GetAudioData(uint32_t index);
volatile int32_t * audio_GetDataPtr(uint32_t index);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__AUDIO_H__*/
