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
#include "dsp/basic_math_functions.h"
#include "dsp/support_functions.h"
#include "dsp/complex_math_functions.h"
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
static volatile int32_t* half_audio_ptr;
static volatile int32_t* full_audio_ptr;
static int32_t imageRef[NUMBER_OF_NOTES] = {0};

/* Private function prototypes -----------------------------------------------*/
static uint32_t greyScale(uint32_t rbg888);
static void synth_IfftMode(volatile int32_t *imageData, volatile int32_t *audioData);

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

	pcm5102_Init();
	half_audio_ptr = pcm5102_GetDataPtr(0);
	full_audio_ptr = pcm5102_GetDataPtr(AUDIO_BUFFER_SIZE * 2);

	arm_fill_q31(65535, (int32_t *)imageRef, NUMBER_OF_NOTES);

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

uint32_t greyScale(uint32_t rbg888)
{
	static uint32_t grey, r, g, b;

	r = rbg888 			& 0xFF; // ___________XXXXX
	g = (rbg888 >> 8) 	& 0xFF; // _____XXXXXX_____
	b = (rbg888 >> 12) 	& 0xFF; // XXXXX___________

	return grey = (r * 299 + g * 587 + b * 114);
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
void synth_DirectMode(volatile int32_t *imageData, volatile int32_t *audioData)
{
	static int32_t signal_R;
	static int32_t image_idx_UP = 0;
	static int32_t image_idx_DW = 0;
	static int32_t buff_idx = 0;
	static int32_t idx = 0;
	static int32_t imageBuffer_q31[CIS_PIXELS_NB];

	for (idx = CIS_PIXELS_NB; --idx >= 0;)
	{
		imageBuffer_q31[idx] = greyScale(imageData[idx]) * 16843;
	}

	for (buff_idx = 0; buff_idx < AUDIO_BUFFER_SIZE; buff_idx++)
	{
		if (image_idx_UP < CIS_PIXELS_NB)
		{
			signal_R = imageBuffer_q31[image_idx_UP];
			image_idx_UP++;
		}
		else
		{
			if (image_idx_DW > 1)
			{
				image_idx_DW--;
				signal_R = imageBuffer_q31[image_idx_DW];
			}
			else
			{
				image_idx_UP = 0;
				image_idx_DW = CIS_PIXELS_NB - 1;
			}
		}

		audioData[buff_idx * 2] = signal_R;
		audioData[buff_idx * 2 + 1] = signal_R;
	}

	shared_var.synth_process_cnt += AUDIO_BUFFER_SIZE;
}
#pragma GCC pop_options

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
void synth_IfftMode(volatile int32_t *imageData, volatile int32_t *audioData)
{
	static int32_t idx, acc, nbAcc;

	static int32_t signal_R;
	static int32_t signal_L;

	static int32_t new_idx;
	static int32_t buff_idx;
	static int32_t note;

	static int32_t imageBuffer_q31[NUMBER_OF_NOTES];
	static float32_t imageBuffer_f32[NUMBER_OF_NOTES];

	static float32_t waveBuffer[AUDIO_BUFFER_SIZE];
	static float32_t ifftBuffer[AUDIO_BUFFER_SIZE];
	static float32_t sumVolumeBuffer[AUDIO_BUFFER_SIZE];
	static float32_t volumeBuffer[AUDIO_BUFFER_SIZE];
	static float32_t maxVolumeBuffer[AUDIO_BUFFER_SIZE];
	static float32_t tmpMaxVolumeBuffer[AUDIO_BUFFER_SIZE];

	arm_fill_f32(0, ifftBuffer, AUDIO_BUFFER_SIZE);
	arm_fill_f32(0, sumVolumeBuffer, AUDIO_BUFFER_SIZE);
	arm_fill_f32(0, maxVolumeBuffer, AUDIO_BUFFER_SIZE);

	for (idx = NUMBER_OF_NOTES; --idx >= 0;)
	{
		imageBuffer_q31[idx] = 0;
		nbAcc = 0;
		for (acc = 6; --acc >= 4;)
		{
			nbAcc++;
			imageBuffer_q31[idx] += greyScale(imageData[(idx * PIXELS_PER_NOTE + acc)]) >> 2;
		}
		imageBuffer_q31[idx] /= nbAcc;
	}

	arm_sub_q31(imageRef, (int32_t *)imageBuffer_q31, (int32_t *)imageBuffer_q31, NUMBER_OF_NOTES);
	arm_clip_q31((int32_t *)imageBuffer_q31, (int32_t *)imageBuffer_q31, 0, 65535, NUMBER_OF_NOTES);

	//handle image / apply different algorithms
#ifdef RELATIVE_MODE
	//relative mode
	arm_sub_q31((int32_t *)imageBuffer_q31, (int32_t *)&imageBuffer_q31[1], (int32_t *)imageBuffer_q31, NUMBER_OF_NOTES - 1);
	arm_clip_q31((int32_t *)imageBuffer_q31, (int32_t *)imageBuffer_q31, 0, 65535, NUMBER_OF_NOTES);
#endif

	for (note = 0; note < NUMBER_OF_NOTES; note++)
	{
		imageBuffer_f32[note] = (float32_t)imageBuffer_q31[note];

		for (buff_idx = 0; buff_idx < AUDIO_BUFFER_SIZE; buff_idx++)
		{
			//octave_coeff jump current pointer into the fundamental waveform, for example : the 3th octave increment the current pointer 8 per 8 (2^3)
			new_idx = (waves[note].current_idx + waves[note].octave_coeff);
			if (new_idx >= waves[note].area_size)
			{
				new_idx -= waves[note].area_size;
			}
			//fill buffer with current note waveform
			waveBuffer[buff_idx] = (*(waves[note].start_ptr + new_idx));
			if (waves[note].octave_divider == 2)
				waveBuffer[++buff_idx] = (*(waves[note].start_ptr + new_idx));
			waves[note].current_idx = new_idx;
		}

#ifdef GAP_LIMITER
		//gap limiter to minimize glitchs
		for (buff_idx = 0; buff_idx < AUDIO_BUFFER_SIZE - 1; buff_idx++)
		{
			if (waves[note].current_volume < imageBuffer_f32[note])
			{
				waves[note].current_volume += waves[note].volume_increment;
				if (waves[note].current_volume > imageBuffer_f32[note])
				{
					waves[note].current_volume = imageBuffer_f32[note];
					//fill buffer with current volume evolution
					break;
				}
			}
			else
			{
				waves[note].current_volume -= waves[note].volume_decrement;
				if (waves[note].current_volume < imageBuffer_f32[note])
				{
					waves[note].current_volume = imageBuffer_f32[note];
					//fill buffer with current volume evolution
					break;
				}
			}

			//fill buffer with current volume evolution
			volumeBuffer[buff_idx] = waves[note].current_volume;
		}

		//fill constant volume buffer
		if (buff_idx < AUDIO_BUFFER_SIZE)
		{
			arm_fill_f32(waves[note].current_volume, &volumeBuffer[buff_idx], AUDIO_BUFFER_SIZE - buff_idx);
		}

#else
		//		waves[note].current_volume = imageBuffer[note];
		arm_fill_f32(imageBuffer[note], volumeBuffer, AUDIO_BUFFER_SIZE);
#endif

		//apply volume scaling at current note waveform
		arm_mult_f32(waveBuffer, volumeBuffer, waveBuffer, AUDIO_BUFFER_SIZE);

		for (buff_idx = AUDIO_BUFFER_SIZE; --buff_idx >= 0;)
		{
			//store max volume
			if (volumeBuffer[buff_idx] > maxVolumeBuffer[buff_idx])
				maxVolumeBuffer[buff_idx] = volumeBuffer[buff_idx];
		}

		//		arm_sub_f32(volumeBuffer, maxVolumeBuffer, tmpMaxVolumeBuffer, AUDIO_BUFFER_SIZE);
		//		arm_clip_f32(tmpMaxVolumeBuffer, tmpMaxVolumeBuffer, 0, 65535, AUDIO_BUFFER_SIZE);
		//		arm_add_f32(maxVolumeBuffer, tmpMaxVolumeBuffer, maxVolumeBuffer, AUDIO_BUFFER_SIZE);


		//ifft summation
		arm_add_f32(waveBuffer, ifftBuffer, ifftBuffer, AUDIO_BUFFER_SIZE);

		//volume summation
		arm_add_f32(volumeBuffer, sumVolumeBuffer, sumVolumeBuffer, AUDIO_BUFFER_SIZE);
	}

	arm_mult_f32(ifftBuffer, maxVolumeBuffer, ifftBuffer, AUDIO_BUFFER_SIZE);
	arm_scale_f32(sumVolumeBuffer, 256, sumVolumeBuffer, AUDIO_BUFFER_SIZE);

	for (buff_idx = 0; buff_idx < AUDIO_BUFFER_SIZE; buff_idx++)
	{
		if (sumVolumeBuffer[buff_idx] != 0)
			signal_R = (int32_t)(ifftBuffer[buff_idx] / (sumVolumeBuffer[buff_idx]));
		else
			signal_R = 0;

		audioData[buff_idx * 2] = signal_R;
		audioData[buff_idx * 2 + 1] = signal_R;
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
void synth_AudioProcess(void)
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
			if (shared_var.mode == IFFT_MODE)
				synth_IfftMode(imageData, half_audio_ptr);
			if (shared_var.mode == DWAVE_MODE)
				synth_DirectMode(imageData, half_audio_ptr);

			SCB_CleanDCache_by_Addr((uint32_t *)half_audio_ptr, AUDIO_BUFFER_SIZE * 4);
			HAL_HSEM_Release(HSEM_ID_0,0);
		}
		else
		{
			//						SCB_InvalidateDCache();
			SCB_InvalidateDCache_by_Addr((uint32_t *)unitary_waveform, WAVEFORM_TABLE_SIZE * 2);
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
			if (shared_var.mode == IFFT_MODE)
				synth_IfftMode(imageData, full_audio_ptr);
			if (shared_var.mode == DWAVE_MODE)
				synth_DirectMode(imageData, full_audio_ptr);

			SCB_CleanDCache_by_Addr((uint32_t *)full_audio_ptr, AUDIO_BUFFER_SIZE * 4);
			HAL_HSEM_Release(HSEM_ID_0,0);
		}
		else
		{
			//						SCB_InvalidateDCache();
			SCB_InvalidateDCache_by_Addr((uint32_t *)unitary_waveform, WAVEFORM_TABLE_SIZE * 2);
			SCB_InvalidateDCache_by_Addr((uint32_t *)waves, sizeof(waves));
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
