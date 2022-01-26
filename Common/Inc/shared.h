/**
 ******************************************************************************
 * @file           : shared.h
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
#include "config.h"
#include "stm32h7xx_hal_sai.h"
#include "arm_math.h"

/* Exported types ------------------------------------------------------------*/
__attribute__ ((packed))
struct wave {
	volatile int16_t *start_ptr;
    uint16_t current_idx;
	uint16_t area_size;
	uint16_t octave_coeff;
	int32_t current_volume;
	int32_t max_gap_per_loop;
	float32_t frequency;
};

__attribute__ ((packed))
struct params {
	int32_t start_frequency;
	int32_t comma_per_semitone;
	int32_t ifft_attack;
	int32_t ifft_release;
	int16_t volume;
};

__attribute__ ((packed))
struct shared_var {
	int32_t synth_process_cnt;
	SAI_HandleTypeDef haudio_out_sai;
};

extern struct shared_var shared_var;
extern volatile struct params params;
extern volatile int32_t cvData[];
extern volatile int32_t imageData[];
extern volatile int16_t audioBuff[];
extern volatile struct wave waves[];
extern volatile int16_t unitary_waveform[];

extern int params_size;

/* Exported constants --------------------------------------------------------*/
#define WAVEFORM_TABLE_SIZE		200000
/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__SHARED_H__*/
