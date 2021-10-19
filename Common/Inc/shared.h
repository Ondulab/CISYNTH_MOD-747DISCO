/**
 ******************************************************************************
 * @file           : shared.c
 * @brief          : shared data structure for both cpu
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SHARED_H__
#define __SHARED_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
__attribute__ ((packed))
struct wave {
	int16_t *start_ptr;
    uint16_t current_idx;
	uint16_t area_size;
	uint16_t octave_coeff;
	int32_t current_volume;
	int32_t phase_polarisation;
	float frequency;
};

extern volatile int16_t __unitary_waveform__;
extern volatile int16_t __unitary_waveform_end__;
extern volatile struct wave __wave__;
extern volatile struct wave __wave_end__;

extern int unitary_waveform_size;
extern int wave_size;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__SHARED_H__*/
