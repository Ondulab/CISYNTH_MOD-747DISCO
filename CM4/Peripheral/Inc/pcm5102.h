/**
 ******************************************************************************
 * @file           : pcm5102.h
 * @brief          : Audio Stereo DAC with 32-bit, 384kHz PCM Interface
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PCM5102_H__
#define __PCM5102_H__

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
void pcm5102_Init(void);
int32_t pcm5102_GetAudioData(uint32_t index);
volatile int32_t * pcm5102_GetDataPtr(uint32_t index);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__PCM5102_H__*/
