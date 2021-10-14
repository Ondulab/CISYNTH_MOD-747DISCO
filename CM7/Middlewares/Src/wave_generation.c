/*
 * wave_generation.c
 *
 *  Created on: 24 avr. 2019
 *      Author: zhonx
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "config.h"
#include "main.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "arm_math.h"

#include "wave_generation.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define COMMA_PER_OCTAVE    ((SEMITONE_PER_OCTAVE) * (COMMA_PER_SEMITONE))

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static float64_t calculate_frequency(uint32_t comma_cnt);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  calculate frequency,
 * @param  comma cnt
 * @retval frequency
 */
static float64_t calculate_frequency(uint32_t comma_cnt)
{
	float64_t frequency = 0.0;
	frequency = START_FREQUENCY * pow(2, (comma_cnt / (12.0 * (COMMA_PER_OCTAVE / (12.0 / (log(2)) * log((START_FREQUENCY * 2.0) / START_FREQUENCY))))));

	return frequency;
}

/**
 * @brief  build_waves,
 * @param  unitary_waveform pointer,
 * @param  waves structure pointer,
 * @retval buffer length on success, negative value otherwise
 */
uint32_t init_waves(int16_t **unitary_waveform, struct wave *waves)
{
	uint32_t buffer_len = 0;
	uint32_t current_unitary_waveform_cell = 0;
	uint32_t note = 0;

	printf("---------- WAVES INIT ---------\n");
	printf("-------------------------------\n");

	//compute cell number for storage all oscillators waveform
	for (uint32_t comma_cnt = 0; comma_cnt < COMMA_PER_OCTAVE; comma_cnt++)
	{
		//store only first octave_coeff frequencies ---- logarithmic distribution
		float64_t frequency = calculate_frequency(comma_cnt);
		buffer_len += (uint32_t)(SAMPLING_FREQUENCY / frequency);
	}

	//allocate the contiguous memory area for storage all waveforms for the first octave_coeff
	*unitary_waveform = malloc(buffer_len * sizeof(uint16_t*));
	if (*unitary_waveform == NULL)
	{
		Error_Handler();
	}

	//compute and store the waveform into unitary_waveform only for the first octave_coeff
	for (uint32_t comma_cnt = 0; comma_cnt < COMMA_PER_OCTAVE; comma_cnt++)
	{
		//compute frequency for each comma into the first octave_coeff
		float64_t frequency = calculate_frequency(comma_cnt);

		//current aera size is the number of char cell for storage a waveform at the current frequency (one pixel per frequency oscillator)
		uint32_t current_aera_size = (uint32_t)(SAMPLING_FREQUENCY / frequency);

		//fill unitary_waveform buffer with sinusoidal waveform for each comma
		for (uint32_t x = 0; x < current_aera_size; x++)
		{
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
#ifdef SIN
				(*unitary_waveform)[current_unitary_waveform_cell] = ((sin((x * 2.00 * PI ) / (float64_t)current_aera_size))) * (WAVE_AMP_RESOLUTION / 2.00);
#endif
#ifdef SAW
				(*unitary_waveform)[current_unitary_waveform_cell] = 0;
				for (uint32_t n = 0; n < 50; n++)
				{
					(*unitary_waveform)[current_unitary_waveform_cell] += pow(-1, n) * (50535 / PI) * sin( (n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / ((float64_t)n + 1.00);
				}
#endif
#ifdef SQR
				(*unitary_waveform)[current_unitary_waveform_cell] = 0;
				for (uint32_t n = 0; n < 50; n++)
				{
					(*unitary_waveform)[current_unitary_waveform_cell] += (2 * 55535 / PI) * sin( (2.00 * n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / (2.00 * (float64_t)n + 1.00);
				}
#endif
				current_unitary_waveform_cell++;
			}
		}

		//for each octave (only the first octave_coeff stay in RAM, for multiple octave_coeff start_ptr stay on first octave waveform but current_ptr jump cell according to multiple frequencies)
		for (uint32_t octave = 0; octave <= MAX_OCTAVE_NUMBER; octave++)
		{
			//compute the current pixel to associate an waveform pointer,
			// *** is current pix, --- octave separation
			// *---------*---------*---------*---------*---------*---------*---------*--------- for current comma at each octave
			// ---*---------*---------*---------*---------*---------*---------*---------*------ for the second comma...
			// ------*---------*---------*---------*---------*---------*---------*---------*---
			// ---------*---------*---------*---------*---------*---------*---------*---------*
			note = comma_cnt + COMMA_PER_OCTAVE * octave;
			//sanity check, if user demand is't possible
			if (note < NUMBER_OF_NOTES)
			{
				//store frequencies
				waves[note].frequency = frequency * pow(2, octave);
				//store octave number
				waves[note].octave_coeff = pow(2, octave);
				//store aera size
				waves[note].area_size = current_aera_size;
				//store pointer address
				waves[note].start_ptr = &(*unitary_waveform)[current_unitary_waveform_cell - current_aera_size];
				//set current pointer at the same address
				waves[note].current_idx = 0;
			}
		}
	}

	if (note < NUMBER_OF_NOTES)
	{
		printf("Configuration fail, current pix : %d\n", (int)note);
		Error_Handler();
	}

	return buffer_len;
}

/**
 * @brief  build_waves,
 * @param  unitary_waveform pointer,
 * @param  waves structure pointer,
 * @retval buffer length on success, negative value otherwise
 */
uint32_t init_waves2(int16_t **unitary_waveform, struct wave *waves)
{
	uint32_t buffer_len = 0;
	uint32_t current_unitary_waveform_cell = 0;
	uint32_t note = 0;

	printf("---------- WAVES INIT ---------\n");
	printf("-------------------------------\n");

	//compute cell number for storage all oscillators waveform (only positive phase)
	for (uint32_t comma_cnt = 0; comma_cnt < COMMA_PER_OCTAVE; comma_cnt++)
	{
		//store only first octave_coeff frequencies ---- logarithmic distribution
		float64_t frequency = calculate_frequency(comma_cnt);
		buffer_len += (uint32_t)(SAMPLING_FREQUENCY / frequency) / 2;
	}

	//allocate the contiguous memory area for storage all waveforms for the first octave_coeff
	*unitary_waveform = malloc(buffer_len * sizeof(uint16_t*));
	if (*unitary_waveform == NULL)
	{
		Error_Handler();
	}

	//compute and store the waveform into unitary_waveform only for the first octave_coeff
	for (uint32_t comma_cnt = 0; comma_cnt < COMMA_PER_OCTAVE; comma_cnt++)
	{
		//compute frequency for each comma into the first octave_coeff
		float64_t frequency = calculate_frequency(comma_cnt);

		//current aera size is the number of cells to storage a waveform at the current frequency (only positive phase)
		uint32_t current_aera_size = (uint32_t)(SAMPLING_FREQUENCY / frequency) / 2;

		//compute the real frequency (discrete errors compensation)
		frequency = SAMPLING_FREQUENCY / (current_aera_size * 2);

		//fill unitary_waveform buffer with positive sinusoidal phase waveform for each comma
		for (uint32_t x = 0; x < current_aera_size; x++)
		{
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				(*unitary_waveform)[current_unitary_waveform_cell] = ((sin((x * PI )/ (float64_t)current_aera_size))) * (WAVE_AMP_RESOLUTION / 2.00);
				current_unitary_waveform_cell++;
			}
		}

		//for each octave (only the first octave_coeff stay in RAM, for multiple octave_coeff start_ptr stay on first octave waveform but current_ptr jump cell according to multiple frequencies)
		for (uint32_t octave = 0; octave <= MAX_OCTAVE_NUMBER; octave++)
		{
			//compute the current pixel to associate an waveform pointer,
			// *** is current pix, --- octave separation
			// *---------*---------*---------*---------*---------*---------*---------*--------- for current comma at each octave
			// ---*---------*---------*---------*---------*---------*---------*---------*------ for the second comma...
			// ------*---------*---------*---------*---------*---------*---------*---------*---
			// ---------*---------*---------*---------*---------*---------*---------*---------*
			note = comma_cnt + COMMA_PER_OCTAVE * octave;
			//sanity check, if user demand is't possible
			if (note < NUMBER_OF_NOTES)
			{
				//store frequencies
				waves[note].frequency = frequency * pow(2, octave);
				//store octave number
				waves[note].octave_coeff = pow(2, octave);
				//store aera size
				waves[note].area_size = current_aera_size;
				//store pointer address
				waves[note].start_ptr = &(*unitary_waveform)[current_unitary_waveform_cell - current_aera_size];
				//set current pointer at the same address
				waves[note].current_idx = 0;
			}
		}
	}

	if (note < NUMBER_OF_NOTES)
	{
		printf("Configuration fail, current pix : %d\n", (int)note);
		Error_Handler();
	}

	return buffer_len;
}

