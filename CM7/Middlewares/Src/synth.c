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
#include "dac.h"

#include "basetypes.h"
#include "arm_math.h"
#include "stdlib.h"
#include "stdio.h"

#include "shared.h"
#include "synth.h"
#include "pcm5102.h"
#include "udp_server.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static volatile int16_t* half_audio_ptr;
static volatile int16_t* full_audio_ptr;

/* Private function prototypes -----------------------------------------------*/
static void synth_IfftMode(volatile int32_t *imageData, volatile int16_t *audioData);

/* Private user code ---------------------------------------------------------*/

/**
 * @brief  synth ifft init.
 * @param
 * @retval Error
 */
int32_t synth_IfftInit(void)
{
	static DAC_ChannelConfTypeDef sConfig;

//	printf("---------- SYNTH INIT ---------\n");
//	printf("-------------------------------\n");

	printf("Note number  = %d\n", (int)NUMBER_OF_NOTES);
	//	printf("Buffer lengh = %d uint16\n", (int)buffer_len);


//	printf("First note Freq = %dHz\nSize = %d\n", (int)waves[0].frequency, (int)waves[0].area_size);
//	printf("Last  note Freq = %dHz\nSize = %d\nOctave = %d\n", (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)waves[NUMBER_OF_NOTES - 1].area_size / (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff), (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));

//	printf("-------------------------------\n");

#ifdef PRINT_IFFT_FREQUENCY
	for (uint32_t note = 0; note < NUMBER_OF_NOTES; note++)
	{
		printf("FREQ = %0.2f, SIZE = %d, OCTAVE = %d\n", waves[note].frequency, (int)waves[note].area_size, (int)waves[note].octave_coeff);
#ifdef PRINT_IFFT_FREQUENCY_FULL
		uint16_t output = 0;
		for (uint32_t idx = 0; idx < (waves[note].area_size / waves[note].octave_coeff); idx++)
		{
			output = *(waves[note].start_ptr + (idx *  waves[note].octave_coeff));
			printf("%d\n", output);
		}
#endif
	}
	printf("-------------------------------\n");
#endif

	/*##-1- Initialize the DAC peripheral ######################################*/
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/*##-1- DAC channel1 Configuration #########################################*/
	//	sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC1_CHANNEL_1) != HAL_OK)
	{
		/* Channel configuration Error */
		Error_Handler();
	}

	/*##-4- Enable DAC Channel1 ################################################*/
	if (HAL_DAC_Start(&hdac1, DAC1_CHANNEL_1) != HAL_OK)
	{
		/* Start Error */
		Error_Handler();
	}

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
void synth_IfftMode(volatile int32_t *imageData, volatile int16_t *audioData)
{
	static int32_t signal_summation_R;
	static int32_t signal_summation_L;
	static uint32_t signal_power_summation;
	static int16_t rfft_R;
	//	static int16_t rfft_L;
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
				current_image_data /= 4;


#else
			current_image_data = (imageData[note - 1] + imageData[note]) / 2;
#endif

			//octave_coeff jump current pointer into the fundamental waveform, for example : the 3th octave increment the current pointer 8 per 8 (2^3)
			//example for 17 cell waveform and 3th octave : [X][Y][Z][X][Y][Z][X][Y][Z][X][Y][[Z][X][Y][[Z][X][Y], X for the first pass, Y for second etc...
			new_idx = (waves[note].current_idx + waves[note].octave_coeff);
			if (new_idx >= waves[note].area_size)
			{
				new_idx -= waves[note].area_size;
			}

#ifdef GAP_LIMITER
				//gap limiter to minimize glitchs
				if (waves[note].current_volume < current_image_data)
				{
					waves[note].current_volume += params.ifft_attack; //IFFT_GAP_PER_MS_INCREASE / (SAMPLING_FREQUENCY / 1000);
					if (waves[note].current_volume > current_image_data)
						waves[note].current_volume = current_image_data;
				}
				else
				{
					waves[note].current_volume -= params.ifft_release; //IFFT_GAP_PER_LOOP_DECREASE / (SAMPLING_FREQUENCY / 1000);
					if (waves[note].current_volume < current_image_data)
						waves[note].current_volume = current_image_data;
				}
#else
				waves[note].current_volume = current_image_data;
#endif
//			}


			if (waves[note].current_volume > max_volume)
				max_volume = waves[note].current_volume;

			//current audio point summation
			signal_summation_R += ((*(waves[note].start_ptr + new_idx)) * waves[note].current_volume) >> 16;
			//			signal_summation_L += ((*(waves[note + 1].start_ptr + new_idx)) * waves[note + 1].current_volume) >> 16;
			//			signal_summation_L += ((*(waves[NUMBER_OF_NOTES - note].start_ptr + new_idx)) * waves[NUMBER_OF_NOTES - note].current_volume) >> 16;

			// 			signal_summation_L = signal_summation_R;

			//read equivalent power of current pixel
			signal_power_summation += waves[note].current_volume;

			waves[note].current_idx = new_idx;
		}

		rfft_R = (signal_summation_R * ((double)max_volume) / (double)signal_power_summation);
		//		rfft_L = (signal_summation_L * ((double)max_volume) / (double)signal_power_summation);

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

	shared_var.synth_process_cnt += AUDIO_BUFFER_SIZE;
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
	static uint32_t cnt = 0;
	static uint32_t last_TRG_state = 0;
	static uint32_t last_RST_state = 0;
	static int32_t i = 0;
	uint32_t tmp_accumulation = 0;

	/* 1st half buffer played; so fill it and continue playing from bottom*/
	if(*pcm5102_GetBufferState() == AUDIO_BUFFER_OFFSET_HALF)
	{
		pcm5102_ResetBufferState();
		udp_serverReceiveImage(imageData);
		/*CM7 try to take the HW sempahore 0*/
		if(HAL_HSEM_FastTake(HSEM_ID_0) == HAL_OK)
		{
			synth_IfftMode(imageData, half_audio_ptr);
			SCB_CleanDCache_by_Addr((uint32_t *)half_audio_ptr, AUDIO_BUFFER_SIZE * 4);
			HAL_HSEM_Release(HSEM_ID_0,0);
		}
		else
		{
			SCB_InvalidateDCache();
//			SCB_InvalidateDCache_by_Addr((uint32_t *)unitary_waveform, (WAVEFORM_TABLE_SIZE * 2) + NUMBER_OF_NOTES * 20);
		}
	}

	/* 2nd half buffer played; so fill it and continue playing from top */
	if(*pcm5102_GetBufferState() == AUDIO_BUFFER_OFFSET_FULL)
	{
		pcm5102_ResetBufferState();
		udp_serverReceiveImage(imageData);
		/*CM7 try to take the HW sempahore 0*/
		if(HAL_HSEM_FastTake(HSEM_ID_0) == HAL_OK)
		{
			synth_IfftMode(imageData, full_audio_ptr);
			SCB_CleanDCache_by_Addr((uint32_t *)full_audio_ptr, AUDIO_BUFFER_SIZE * 4);
			HAL_HSEM_Release(HSEM_ID_0,0);
		}
		else
		{
			SCB_InvalidateDCache();
//			SCB_InvalidateDCache_by_Addr((uint32_t *)unitary_waveform, (WAVEFORM_TABLE_SIZE * 2) + NUMBER_OF_NOTES * 20);
		}
	}

#ifdef CV
	if (HAL_GPIO_ReadPin(ARD_D2_GPIO_Port, ARD_D2_Pin) == FALSE)
	{
		if (last_RST_state == TRUE)
			cnt = 0;
		last_RST_state = FALSE;
	}
	else
	{
		last_RST_state = TRUE;
	}
	if (HAL_GPIO_ReadPin(ARD_D7_GPIO_Port, ARD_D7_Pin) == TRUE)
	{
		if (last_TRG_state != TRUE)
			cnt += IMAGE_WEIGHT;

		last_TRG_state = TRUE;
	}
	else
	{
		last_TRG_state = FALSE;
	}

	if (cnt >= (NUMBER_OF_NOTES))
		cnt = 0;

	/*##-5- Set DAC channel1 DHR12RD register ################################################*/

	for (i = 0; i < IMAGE_WEIGHT; i++)
	{
		if ((cnt + i) < NUMBER_OF_NOTES)
			tmp_accumulation += (imageData[cnt + i] >> 4);
	}

	tmp_accumulation /= i;
	cvData[cnt / IMAGE_WEIGHT - 1] = tmp_accumulation;

	if (HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, tmp_accumulation) != HAL_OK)
	{
		/* Setting value Error */
		Error_Handler();
	}
#endif
}
