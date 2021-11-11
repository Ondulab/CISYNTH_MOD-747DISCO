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

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static float64_t calculate_frequency(uint32_t comma_cnt, struct waveParams *params);
static uint32_t calculate_waveform(uint32_t current_aera_size, uint32_t current_unitary_waveform_cell, uint32_t buffer_len, struct waveParams *params);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  calculate frequency,
 * @param  comma cnt
 * @retval frequency
 */
static float64_t calculate_frequency(uint32_t comma_cnt, struct waveParams *params)
{
	float64_t frequency = 0.0;
	frequency = params->startFrequency * pow(2, (comma_cnt / (12.0 * ((SEMITONE_PER_OCTAVE * params->commaPerSemitone) / (12.0 / (log(2)) * log((params->startFrequency * 2.0) / params->startFrequency))))));

	return frequency;
}

/**
 * @brief  calculate waveform,
 * @param  current_area_size,
 * @param  current_unitary_waveform_cell,
 * @param  buffer_len,
 * @param  waveParams *params,
 * @retval current_unitary_waveform_cell
 */
static uint32_t calculate_waveform(uint32_t current_aera_size, uint32_t current_unitary_waveform_cell, uint32_t buffer_len, struct waveParams *params)
{
	unitary_waveform[current_unitary_waveform_cell] = 0;
	uint32_t max = 0;
	uint32_t currentValue = 0;
	uint32_t overshootCompensation = 0;

	switch (params->waveformType)
	{
	case SIN_WAVE:
		//fill unitary_waveform buffer with sinusoidal waveform for each comma
		for (uint32_t x = 0; x < current_aera_size; x++)
		{
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				unitary_waveform[current_unitary_waveform_cell] = ((sin((x * 2.00 * PI ) / (float64_t)current_aera_size))) * (WAVE_AMP_RESOLUTION / 2.00);
			}
			current_unitary_waveform_cell++;
		}
		break;
	case SAW_WAVE:
		//compute de maximum overshoot value on positive phase
		for (uint32_t x = 0; x < (current_aera_size / 2); x++)
		{
			currentValue = 0;
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				//store overshoot value
				for (uint32_t n = 0; n < params->waveformOrder; n++)
				{
					currentValue += pow(-1, n) * (WAVE_AMP_RESOLUTION / PI) * sin( (n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / ((float64_t)n + 1.00);
					if (currentValue > max)
						max = currentValue;
				}
			}
		}
		//compute overshoot compensation
		overshootCompensation = ((max * 2) - WAVE_AMP_RESOLUTION);
		//fill unitary_waveform buffer with saw waveform for each comma
		for (uint32_t x = 0; x < current_aera_size; x++)
		{
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				for (uint32_t n = 0; n < params->waveformOrder; n++)
				{
					unitary_waveform[current_unitary_waveform_cell] += pow(-1, n) * ((WAVE_AMP_RESOLUTION - overshootCompensation) / PI) * sin( (n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / ((float64_t)n + 1.00);
				}
			}
			current_unitary_waveform_cell++;
		}
		break;
	case SQR_WAVE:
		//compute de maximum overshoot value on positive phase
		for (uint32_t x = 0; x < (current_aera_size / 2); x++)
		{
			currentValue = 0;
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				//store overshoot value
				for (uint32_t n = 0; n < params->waveformOrder; n++)
				{
					currentValue += (2 * WAVE_AMP_RESOLUTION / PI) * sin( (2.00 * n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / (2.00 * (float64_t)n + 1.00);
					if (currentValue > max)
						max = currentValue;
				}
			}
		}
		//compute overshoot compensation
		overshootCompensation = ((max * 2) - WAVE_AMP_RESOLUTION);
		//fill unitary_waveform buffer with square waveform for each comma
		for (uint32_t x = 0; x < current_aera_size; x++)
		{
			//sanity check
			if (current_unitary_waveform_cell < buffer_len)
			{
				for (uint32_t n = 0; n < params->waveformOrder; n++)
				{
					unitary_waveform[current_unitary_waveform_cell] += (2 * (WAVE_AMP_RESOLUTION - overshootCompensation) / PI) * sin( (2.00 * n + 1.00) * x * 2.00 * PI / (float64_t)current_aera_size) / (2.00 * (float64_t)n + 1.00);
				}
			}
			current_unitary_waveform_cell++;
		}
		break;
	}

	return current_unitary_waveform_cell;
}

/**
 * @brief  build_waves,
 * @param  unitary_waveform pointer,
 * @param  waves structure pointer,
 * @param  params wave parameters,
 * @retval buffer length on success, negative value otherwise
 */
uint32_t init_waves(volatile int16_t *unitary_waveform, volatile struct wave *waves, struct waveParams *params)
{
	uint32_t buffer_len = 0;
	uint32_t current_unitary_waveform_cell = 0;
	uint32_t note = 0;

	printf("---------- WAVES INIT ---------\n");
	printf("-------------------------------\n");

	//compute cell number for storage all oscillators waveform
	for (uint32_t comma_cnt = 0; comma_cnt < (SEMITONE_PER_OCTAVE * params->commaPerSemitone); comma_cnt++)
	{
		//store only first octave_coeff frequencies ---- logarithmic distribution
		float64_t frequency = calculate_frequency(comma_cnt, params);
		buffer_len += (uint32_t)(SAMPLING_FREQUENCY / frequency);
	}

	//todo add check buffer_len size

	//compute and store the waveform into unitary_waveform only for the first octave_coeff
	for (uint32_t comma_cnt = 0; comma_cnt < (SEMITONE_PER_OCTAVE * params->commaPerSemitone); comma_cnt++)
	{
		//compute frequency for each comma into the first octave_coeff
		float64_t frequency = calculate_frequency(comma_cnt, params);

		//current aera size is the number of char cell for storage a waveform at the current frequency (one pixel per frequency oscillator)
		uint32_t current_aera_size = (uint32_t)(SAMPLING_FREQUENCY / frequency);

		current_unitary_waveform_cell = calculate_waveform(current_aera_size, current_unitary_waveform_cell, buffer_len, params);

		//for each octave (only the first octave_coeff stay in RAM, for multiple octave_coeff start_ptr stay on first octave waveform but current_ptr jump cell according to multiple frequencies)
		for (uint32_t octave = 0; octave <= (NUMBER_OF_NOTES / (SEMITONE_PER_OCTAVE * params->commaPerSemitone)); octave++)
		{
			//compute the current pixel to associate an waveform pointer,
			// *** is current pix, --- octave separation
			// *---------*---------*---------*---------*---------*---------*---------*--------- for current comma at each octave
			// ---*---------*---------*---------*---------*---------*---------*---------*------ for the second comma...
			// ------*---------*---------*---------*---------*---------*---------*---------*---
			// ---------*---------*---------*---------*---------*---------*---------*---------*
			note = comma_cnt + (SEMITONE_PER_OCTAVE * params->commaPerSemitone) * octave;
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
				waves[note].start_ptr = &unitary_waveform[current_unitary_waveform_cell - current_aera_size];
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
 * @param  params wave parameters,
 * @retval buffer length on success, negative value otherwise
 */
uint32_t init_waves2(volatile int16_t *unitary_waveform, volatile struct wave *waves, struct waveParams *params)
{
	uint32_t buffer_len = 0;
	uint32_t current_unitary_waveform_cell = 0;
	uint32_t note = 0;

	printf("---------- WAVES INIT ---------\n");
	printf("-------------------------------\n");

	//compute cell number for storage all oscillators waveform (only positive phase)
	for (uint32_t comma_cnt = 0; comma_cnt < (SEMITONE_PER_OCTAVE * params->commaPerSemitone); comma_cnt++)
	{
		//store only first octave_coeff frequencies ---- logarithmic distribution
		float64_t frequency = calculate_frequency(comma_cnt, params);
		buffer_len += (uint32_t)(SAMPLING_FREQUENCY / frequency) / 2;
	}

	//allocate the contiguous memory area for storage all waveforms for the first octave_coeff
	//	*unitary_waveform = malloc(buffer_len * sizeof(uint16_t*));
	//	if (*unitary_waveform == NULL)
	//	{
	//		Error_Handler();
	//	}

	//compute and store the waveform into unitary_waveform only for the first octave_coeff
	for (uint32_t comma_cnt = 0; comma_cnt < (SEMITONE_PER_OCTAVE * params->commaPerSemitone); comma_cnt++)
	{
		//compute frequency for each comma into the first octave_coeff
		float64_t frequency = calculate_frequency(comma_cnt, params);

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
				unitary_waveform[current_unitary_waveform_cell] = ((sin((x * PI )/ (float64_t)current_aera_size))) * (WAVE_AMP_RESOLUTION / 2.00);
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
			note = comma_cnt + (SEMITONE_PER_OCTAVE * params->commaPerSemitone) * octave;
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
				waves[note].start_ptr = &unitary_waveform[current_unitary_waveform_cell - current_aera_size];
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

