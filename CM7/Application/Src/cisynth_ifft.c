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
	uint32_t aRandom32bit_Note = 0;
	uint32_t aRandom32bit_Volume = 0;
	uint32_t aRandom32bit_Repeat = 100;

	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	synth_IfftInit();

	start_tick = HAL_GetTick();

	while (1)
	{
		MX_LWIP_Process();
		synth_AudioProcess(IFFT_MODE);

		if (HAL_GetTick() - start_tick >= aRandom32bit_Repeat)
		{

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
			synth_SetImageData(aRandom32bit_Note % (NUMBER_OF_NOTES - 1), aRandom32bit_Volume % 32000);

			if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit_Note) != HAL_OK)
			{
				/* Random number generation error */
				Error_Handler();
			}

			if (aRandom32bit_Note > 3800000000)
			{
				for (uint32_t y = 0; y < NUMBER_OF_NOTES - 1; y++)
				{
					if ((aRandom32bit_Volume % 32000) < synth_GetImageData(y))
						synth_SetImageData(y, synth_GetImageData(y) - (aRandom32bit_Volume % 32000));
					else
						synth_SetImageData(y, 0);
				}
			}

			if (HAL_RNG_GenerateRandomNumber(&hrng, &aRandom32bit_Repeat) != HAL_OK)
			{
				/* Random number generation error */
				Error_Handler();
			}

			aRandom32bit_Repeat = aRandom32bit_Repeat % 200 + 50;

			start_tick = HAL_GetTick();
		}
	}
}
#pragma GCC pop_options
