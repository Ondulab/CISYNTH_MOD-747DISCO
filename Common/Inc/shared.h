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

typedef enum {
	IFFT_MODE = 0,
	DWAVE_MODE,
	MENU_MODE
}synthModeTypeDef;

struct wave {
	volatile float32_t *start_ptr;
    uint32_t current_idx;
	uint32_t area_size;
	uint32_t octave_coeff;
	uint32_t octave_divider;
	float32_t current_volume;
	float32_t volume_increment;
	float32_t max_volume_increment;
	float32_t volume_decrement;
	float32_t max_volume_decrement;
	float32_t frequency;
};

struct params {
	int32_t start_frequency;
	int32_t comma_per_semitone;
	int32_t ifft_attack;
	int32_t ifft_release;
	int32_t volume;
};

struct shared_var {
	synthModeTypeDef mode;
	int32_t synth_process_cnt;
	SAI_HandleTypeDef haudio_out_sai;
};

/* Exported constants --------------------------------------------------------*/
#define WAVEFORM_TABLE_SIZE		90000

extern struct shared_var shared_var;
extern volatile struct params params;
extern volatile int32_t cvData[];
extern volatile int32_t imageData[];
extern volatile int32_t audioBuff[];
extern volatile struct wave waves[NUMBER_OF_NOTES];
extern volatile float32_t unitary_waveform[WAVEFORM_TABLE_SIZE];

extern int params_size;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__SHARED_H__*/
