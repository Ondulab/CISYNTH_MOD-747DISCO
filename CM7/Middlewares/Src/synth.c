/*
 * synth.c
 *
 *  Created on: 24 avr. 2019
 *      Author: zhonx
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "config.h"
#include "rng.h"

#include "basetypes.h"
#include "arm_math.h"
#include "stdlib.h"
#include "stdio.h"

#include "wave_generation.h"
#include "synth.h"
#include "pcm5102.h"
#include "menu.h"
#include "udp_server.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static int16_t *unitary_waveform = NULL;
static struct wave waves[NUMBER_OF_NOTES];
volatile uint32_t synth_process_cnt = 0;
static int16_t* half_audio_ptr;
static int16_t* full_audio_ptr;

/* Variable containing black and white frame from CIS*/
static int32_t *imageData = NULL;
//static uint16_t imageData[((CIS_END_CAPTURE * CIS_ADC_OUT_LINES) / CIS_IFFT_OVERSAMPLING_RATIO) - 1]; // for debug

/* Private function prototypes -----------------------------------------------*/
static void synth_IfftMode(int32_t *imageData, int16_t *audioData);
static void synth_IfftMode2(int32_t *imageData, int16_t *audioData);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  synth ifft init.
 * @param
 * @retval Error
 */
int32_t synth_IfftInit(void)
{
	int32_t buffer_len = 0;
	uint32_t aRandom32bit = 0;

	printf("---------- SYNTH INIT ---------\n");
	printf("-------------------------------\n");

	//allocate the contiguous memory area for storage image data
	imageData = malloc(NUMBER_OF_NOTES * sizeof(int32_t*));
	if (imageData == NULL)
	{
		Error_Handler();
	}

	memset(imageData, 0, NUMBER_OF_NOTES * sizeof(int32_t*));

#ifdef IFFT_1
	buffer_len = init_waves(&unitary_waveform, waves);
#else
	buffer_len = init_waves2(&unitary_waveform, waves);
#endif

	// start with random index
	for (uint32_t i = 0; i < NUMBER_OF_NOTES; i++)
	{
		if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit) != HAL_OK)
		{
			/* Random number generation error */
			Error_Handler();
		}
		waves[i].current_idx = aRandom32bit % waves[i].area_size;
		waves[i].current_volume = 0;
		waves[i].phase_polarisation = 1;
	}

	if (buffer_len < 0)
	{
		printf("RAM overflow");
		Error_Handler();
		return -1;
	}

	printf("Note number  = %d\n", (int)NUMBER_OF_NOTES);
	printf("Buffer lengh = %d uint16\n", (int)buffer_len);


	uint8_t FreqStr[256] = {0};
	UTIL_LCD_FillRect(0, DISPLAY_AERA2_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_AERAS2_HEIGHT, UTIL_LCD_COLOR_BLACK);
	sprintf((char *)FreqStr, " %d -> %dHz      Octave:%d", (int)waves[0].frequency, (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));
	UTIL_LCD_DisplayStringAt(0, DISPLAY_AERA2_Y1POS, (uint8_t*)FreqStr, LEFT_MODE);

	printf("First note Freq = %dHz\nSize = %d\n", (int)waves[0].frequency, (int)waves[0].area_size);
	printf("Last  note Freq = %dHz\nSize = %d\nOctave = %d\n", (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)waves[NUMBER_OF_NOTES - 1].area_size / (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff), (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));

	printf("-------------------------------\n");

#ifdef PRINT_IFFT_FREQUENCY
	for (uint32_t pix = 0; pix < NUMBER_OF_NOTES; pix++)
	{
		printf("FREQ = %0.2f, SIZE = %d, OCTAVE = %d\n", waves[pix].frequency, (int)waves[pix].area_size, (int)waves[pix].octave_coeff);
#ifdef PRINT_IFFT_FREQUENCY_FULL
		uint16_t output = 0;
		for (uint32_t idx = 0; idx < (waves[pix].area_size / waves[pix].octave_coeff); idx++)
		{
			output = *(waves[pix].start_ptr + (idx *  waves[pix].octave_coeff));
			printf("%d\n", output);
		}
#endif
	}
	printf("-------------------------------\n");
#endif

	udp_serverInit();
	pcm5102_Init();
	half_audio_ptr = pcm5102_GetDataPtr(0);
	full_audio_ptr = pcm5102_GetDataPtr(AUDIO_BUFFER_SIZE * 2);

	return 0;
}

/**
 * @brief  Get Image buffer data
 * @param  Index
 * @retval Value
 */
int32_t synth_GetImageData(uint32_t index)
{
	//	if (index >= RFFT_BUFFER_SIZE)
	//		Error_Handler();
	return imageData[index];
}

/**
 * @brief  Set Image buffer data
 * @param  Index
 * @retval Value
 */
int32_t synth_SetImageData(uint32_t index, int32_t value)
{
	//	if (index >= RFFT_BUFFER_SIZE)
	//		Error_Handler();
	imageData[index] = value;
	return 0;
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
void synth_IfftMode(int32_t *imageData, int16_t *audioData)
{
	static int32_t signal_summation_R;
	static int32_t signal_summation_L;
	static uint32_t signal_power_summation;
	static int16_t rfft_R;
	static int16_t rfft_L;
	static uint16_t new_idx;
	static uint32_t write_data_nbr;
	static int32_t note;
	static int32_t max_volume;
	static int32_t current_image_data;

	write_data_nbr = 0;

	while(write_data_nbr < AUDIO_BUFFER_SIZE)
	{
		signal_summation_R = 0;
		signal_summation_L = 0;
		signal_power_summation = 0;
		max_volume = 0;

		//Summation for all pixel
		for (note = NUMBER_OF_NOTES; --note >= 5;)
		{
#ifdef RELATIVE_MODE
			//relative mode
			if (imageData[note - 1] - imageData[note] > 0)
				current_image_data = imageData[note - 1] - imageData[note];
			else
				current_image_data = 0;//imageData[note] - imageData[note - 1];

			if (current_image_data < NOISE_REDUCER)
				current_image_data /= 2;


#else
			current_image_data = (imageData[note - 1] + imageData[note]) / 2;
#endif

			//octave_coeff jump current pointer into the fundamental waveform, for example : the 3th octave increment the current pointer 8 per 8 (2^3)
			//example for 17 cell waveform and 3th octave : [X][Y][Z][X][Y][Z][X][Y][Z][X][Y][[Z][X][Y][[Z][X][Y], X for the first pass, Y for second etc...
			new_idx = (waves[note].current_idx + waves[note].octave_coeff);
			if (new_idx >= waves[note].area_size)
			{
				new_idx -= waves[note].area_size;

#ifdef GAP_LIMITER
				//gap limiter to minimize glitchs
				if (waves[note].current_volume < current_image_data)
				{
					waves[note].current_volume += IFFT_GAP_PER_MS_INCREASE / (SAMPLING_FREQUENCY / 1000);
					if (waves[note].current_volume > current_image_data)
						waves[note].current_volume = current_image_data;
				}
				else
				{
					waves[note].current_volume -= IFFT_GAP_PER_MS_DECREASE / (SAMPLING_FREQUENCY / 1000);
					if (waves[note].current_volume < current_image_data)
						waves[note].current_volume = current_image_data;
				}
#else
				waves[note].current_volume = current_image_data;
#endif
			}


			if (waves[note].current_volume > max_volume)
				max_volume = waves[note].current_volume;

			//current audio point summation
			signal_summation_R += ((*(waves[note].start_ptr + new_idx)) * waves[note].current_volume) >> 16;
			signal_summation_L += ((*(waves[note + 1].start_ptr + new_idx)) * waves[note + 1].current_volume) >> 16;
			//			signal_summation_L += ((*(waves[NUMBER_OF_NOTES - note].start_ptr + new_idx)) * waves[NUMBER_OF_NOTES - note].current_volume) >> 16;

			// 			signal_summation_L = signal_summation_R;

			//read equivalent power of current pixel
			signal_power_summation += waves[note].current_volume;

			waves[note].current_idx = new_idx;
		}

		rfft_R = (signal_summation_R * ((double)max_volume) / (double)signal_power_summation);
		rfft_L = (signal_summation_L * ((double)max_volume) / (double)signal_power_summation);

		//		rfft_R = (signal_summation_R * (65535.00) / (double)signal_power_summation);
		//		rfft_L = (signal_summation_L * (65535.00) / (double)signal_power_summation);

#ifdef STEREO_1
		audioData[write_data_nbr * 2] = rfft_L;		//L
#else
		audioData[write_data_nbr * 2] = rfft_R;
#endif
		audioData[write_data_nbr * 2 + 1] = rfft_R;	//R
		write_data_nbr++;
	}

	synth_process_cnt += AUDIO_BUFFER_SIZE;
}
#pragma GCC pop_options

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
void synth_IfftMode2(int32_t *imageData, int16_t *audioData)
{
	static int32_t tempWaveformBuffer[AUDIO_BUFFER_SIZE * 2];
	static int32_t tempVolumeBuffer[AUDIO_BUFFER_SIZE * 2];
	static int32_t tempWaveformBufferSummation[AUDIO_BUFFER_SIZE];
	static int32_t tempVolumeBufferSummation[AUDIO_BUFFER_SIZE];
	static int32_t tempMaxVolumeBuffer[AUDIO_BUFFER_SIZE];
	static int16_t rfft_R;
	static int16_t rfft_L;
	static int32_t note;
	static uint32_t area_size;

	arm_fill_q31(0, tempWaveformBufferSummation, AUDIO_BUFFER_SIZE);
	arm_fill_q31(0, tempVolumeBufferSummation, AUDIO_BUFFER_SIZE);
	arm_fill_q31(0, tempMaxVolumeBuffer, AUDIO_BUFFER_SIZE);

	//Summation for all pixel
	for (note = NUMBER_OF_NOTES; --note > 1;)
		//	note = 60;
	{
		uint32_t temp_buff_idx = 0;
		uint32_t generation_step = 0;
		uint32_t start_copy_idx = 0;

		//fill temporary waveform buffer
		while (temp_buff_idx < AUDIO_BUFFER_SIZE)
		{
			waves[note].current_idx += waves[note].octave_coeff;
			//detect the end of buffer (y = 0)
			if (waves[note].current_idx >= waves[note].area_size)
			{
				//return to the wave beginning
				waves[note].current_idx -= waves[note].area_size;

				//store the new volume
//				waves[note].current_volume = abs(imageData[note] - imageData[note - 1]);

				//add
				static int32_t current_image_data;

				if (imageData[note - 1] - imageData[note] > 0)
					current_image_data = imageData[note - 1] - imageData[note];
				else
					current_image_data = 0;//imageData[note] - imageData[note - 1];

				waves[note].current_volume = current_image_data;
				//endadd

				generation_step++;

				waves[note].phase_polarisation *= -1;

				//store the start index for DSP
				if (generation_step == 1)
					start_copy_idx = temp_buff_idx;
			}

			//fill the temporary buffer with waveform table for old and new volume
			if (generation_step < 2)
			{
				//fill the two first alternations
				tempWaveformBuffer[temp_buff_idx] = (((*(waves[note].start_ptr + waves[note].current_idx)) * waves[note].current_volume) >> 16) * waves[note].phase_polarisation;
				//store the current volume
				tempVolumeBuffer[temp_buff_idx] = waves[note].current_volume;

				if (waves[note].current_volume > tempMaxVolumeBuffer[temp_buff_idx])
					tempMaxVolumeBuffer[temp_buff_idx] =  waves[note].current_volume;

				temp_buff_idx++;
			}
			else
			{
				//fill the rest with current volume
				arm_fill_q31(waves[note].current_volume, &tempVolumeBuffer[temp_buff_idx], AUDIO_BUFFER_SIZE - temp_buff_idx);
				arm_fill_q31(tempMaxVolumeBuffer[temp_buff_idx - 1], &tempMaxVolumeBuffer[temp_buff_idx], AUDIO_BUFFER_SIZE - temp_buff_idx);

				area_size = temp_buff_idx - start_copy_idx;

				waves[note].phase_polarisation *= -1;

				//second stage for DSP duplications
				while (temp_buff_idx < AUDIO_BUFFER_SIZE)
				{
					//duplicate and invert alternations_
					arm_copy_q31(&tempWaveformBuffer[start_copy_idx], &tempWaveformBuffer[temp_buff_idx], area_size);
					arm_negate_q31(&tempWaveformBuffer[temp_buff_idx], &tempWaveformBuffer[temp_buff_idx], area_size);
					waves[note].phase_polarisation *= -1;

					start_copy_idx = temp_buff_idx;
					temp_buff_idx += area_size;
				}
			}
		}

		//update current index after DSP duplications
		waves[note].current_idx = (AUDIO_BUFFER_SIZE - start_copy_idx) * waves[note].octave_coeff;

		//wave accumulator
		arm_add_q31(tempWaveformBufferSummation, tempWaveformBuffer, tempWaveformBufferSummation, AUDIO_BUFFER_SIZE);

		//volume accumulator
		arm_add_q31(tempVolumeBufferSummation, tempVolumeBuffer, tempVolumeBufferSummation, AUDIO_BUFFER_SIZE);
	}

	for (uint32_t idx = 0; idx < AUDIO_BUFFER_SIZE; idx++)
	{
		if (tempVolumeBufferSummation[idx] != 0)
			rfft_R = ((tempWaveformBufferSummation[idx] * (float64_t)(tempMaxVolumeBuffer[idx])) / (float64_t)(tempVolumeBufferSummation[idx]));
		rfft_L = rfft_R;

		audioData[idx * 2] = rfft_R;
		audioData[idx * 2 + 1] = rfft_L;
	}

	synth_process_cnt += AUDIO_BUFFER_SIZE;
}
#pragma GCC pop_options

/**
 * @brief  Manages Audio process.
 * @param  None
 * @retval Audio error
 *
 *                   |------------------------------|------------------------------|
 *                   |half rfft buffer to audio buff|                              |
 * audio buffer      |------------FILL--------------|-------------PLAY-------------|
 *                   |                              |                              |
 *                   |                              |     fill half rfft buffer    |
 *                   |                              |                              |
 *                   |------------------------------|------------------------------|
 *                                                  ^
 *                                                HALF
 *                                              COMPLETE
 *
 *                   |------------------------------|------------------------------|
 *                   |                              |full rfft buffer to audio buff|
 * audio buffer      |-------------PLAY-------------|-------------FILL-------------|
 *                   |                              |                              |
 *                   |     fill full rfft buffer    |                              |
 *                   |                              |                              |
 *                   |------------------------------|------------------------------|
 *                                                                                 ^
 *                                                                                FULL
 *                                                                              COMPLETE
 */
void synth_AudioProcess(synthModeTypeDef mode)
{
	/* 1st half buffer played; so fill it and continue playing from bottom*/
	if(*pcm5102_GetBufferState() == AUDIO_BUFFER_OFFSET_HALF)
	{
		pcm5102_ResetBufferState();
		udp_serverReceiveImage(imageData);
#ifdef IFFT_1
		synth_IfftMode(imageData, half_audio_ptr);
#else
		synth_IfftMode2(imageData, half_audio_ptr);
#endif
		SCB_CleanDCache_by_Addr((uint32_t *)half_audio_ptr, AUDIO_BUFFER_SIZE * 4);
	}

	/* 2nd half buffer played; so fill it and continue playing from top */
	if(*pcm5102_GetBufferState() == AUDIO_BUFFER_OFFSET_FULL)
	{
		pcm5102_ResetBufferState();
		udp_serverReceiveImage(imageData);
#ifdef IFFT_1
		synth_IfftMode(imageData, full_audio_ptr);
#else
		synth_IfftMode2(imageData, full_audio_ptr);
#endif
		SCB_CleanDCache_by_Addr((uint32_t *)full_audio_ptr, AUDIO_BUFFER_SIZE * 4);
	}
}
