/*
 * wave_generation.h
 *
 *  Created on: 24 avr. 2019
 *      Author: zhonx
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WAVE_GENERATION_H
#define __WAVE_GENERATION_H

/* Includes ------------------------------------------------------------------*/
#include "synth.h"
#include "shared.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
	SAW_WAVE,
	SIN_WAVE,
	SQR_WAVE
} waveformType;

typedef enum {
	MAJOR,
	MINOR,
} harmonizationType;

struct waveParams {
	uint16_t commaPerSemitone;
	uint16_t startFrequency;
	harmonizationType harmonizationType;
	uint16_t harmonizationLevel;
	waveformType waveformType;
    uint16_t waveformOrder;
};

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
uint32_t init_waves(volatile int16_t *unitary_waveform, volatile struct wave *waves, volatile struct waveParams *params);
uint32_t init_waves2(volatile int16_t *unitary_waveform, volatile struct wave *waves, volatile struct waveParams *params);

/* Private defines -----------------------------------------------------------*/

#endif /* __WAVE_GENERATION_H */
