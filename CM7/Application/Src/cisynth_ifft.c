/*
 * cisynth_eth.c
 *
 *  Created on: May 31, 2020
 *      Author: zhonx
 */

#include "main.h"

#include "cisynth_ifft.h"
#include "synth.h"
#include "config.h"
#include "pcm5102.h"
#include "rng.h"

#include "lwip.h"

#include "stdio.h"
#include "stdbool.h"

extern __IO uint32_t synth_process_cnt;

/**
 * @brief  The application entry point.
 * @retval int
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
int cisynth_ifft(void)
{
	static uint32_t start_tick;
	static uint32_t note = 10;
	uint32_t aRandom32bit_Note = 0;
	uint32_t aRandom32bit_Volume = 0;
	uint32_t aRandom32bit_Repeat = 100;
	uint32_t demoNoteTable[10] = {0};
	uint32_t tmp_demoNoteTable[10] = {0};
	uint32_t index = 0;

	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	synth_IfftInit();

	start_tick = HAL_GetTick();

	while (1)
	{
		MX_LWIP_Process();
		synth_AudioProcess(IFFT_MODE);

		if (HAL_GetTick() - start_tick >= 10)// aRandom32bit_Repeat)
		{
			//			if (note > NUMBER_OF_NOTES - 11)
			//			{
			//				synth_SetImageData(note - 10, 0);
			//				note = 10;
			//			}
			//
			//			synth_SetImageData(note - 10, 0);
			//			synth_SetImageData(note, 10500);
			//
			//			note+= 10;
			//
			if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit_Note) != HAL_OK)
			{
				/* Random number generation error */
				Error_Handler();
			}

			if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit_Volume) != HAL_OK)
			{
				/* Random number generation error */
				Error_Handler();
			}

			if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit_Repeat) != HAL_OK)
			{
				/* Random number generation error */
				Error_Handler();
			}

			tmp_demoNoteTable[index++] = aRandom32bit_Note % (NUMBER_OF_NOTES - 1);
			if (index > 9)
					index = 0;

			synth_SetImageData(tmp_demoNoteTable[0], aRandom32bit_Volume % 32000);

			synth_SetImageData(tmp_demoNoteTable[(index - 10) % 10], 0);

//			aRandom32bit_Repeat = aRandom32bit_Repeat % 500 + 10;

			start_tick = HAL_GetTick();
		}
	}
}
#pragma GCC pop_options
