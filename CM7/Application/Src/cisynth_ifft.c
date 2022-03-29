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
#include "shared.h"

#include "lwip.h"

#include "udp_server.h"

#include "stdio.h"
#include "stdbool.h"

extern __IO uint32_t synth_process_cnt;

void imageEmulator_toggle(void);
void imageEmulator_slide(void);
void imageEmulator_volume(void);
void imageEmulator_random(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
int cisynth_ifft(void)
{
	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	udp_serverInit();
	//	udp_clientInit();

	synth_IfftInit();

	//	arm_fill_q31(65535, (int32_t *)imageData, NUMBER_OF_NOTES);
	//	synth_SetImageData(87, 65000);
	//	synth_SetImageData(70, 65535);
	//	synth_SetImageData(30, 35535);

	while (1)
	{
		MX_LWIP_Process();
		synth_AudioProcess(IFFT_MODE);

		//		imageEmulator_toggle();
//		imageEmulator_slide();
		//		imageEmulator_random();
		imageEmulator_volume();
	}
}

void imageEmulator_toggle(void)
{
	static uint32_t start_tick = 0;
	static uint32_t note = 1;
	static uint32_t volume = 65000;

	if (HAL_GetTick() - start_tick >= 100)
	{
		synth_SetImageData(note, volume);
	}

	if (HAL_GetTick() - start_tick >= 200)
	{
		synth_SetImageData(note, 0);

		if (note < (NUMBER_OF_NOTES - 1))
		{
			note++;
		}
		else
		{
			synth_SetImageData(note, 0);
			note = 1;
		}
		start_tick = HAL_GetTick();
	}
}

void imageEmulator_slide(void)
{
	static uint32_t start_tick = 0;
	static uint32_t note = 0;
	static uint32_t volume = 65000;

	if (HAL_GetTick() - start_tick >= 50)
	{
		if (note > 0)
		{
			synth_SetImageData(note - 1, 0);
		}
		if (note < NUMBER_OF_NOTES)
		{
			synth_SetImageData(note, volume);
			note++;
		}
		else
		{
			note = 0;
		}
		start_tick = HAL_GetTick();
	}
}

void imageEmulator_volume(void)
{
	static uint32_t start_tick = 0;
	static uint32_t note = 50;
	static int32_t volume = 0;
	static int32_t dir = 0;

	if (HAL_GetTick() - start_tick >= 1)
	{
		if (dir == 0)
		{
			if (volume <= 65535)
			{
				synth_SetImageData(note, volume);
				volume+=100;
			}
			else
			{
				dir = 1;
				volume = 65535;
			}
		}
		else
		{
			if (volume > 0)
			{
				synth_SetImageData(note, volume);
				volume-=100;
			}
			else
			{
				dir = 0;
				volume = 0;
			}
		}
		start_tick = HAL_GetTick();
	}
}

void imageEmulator_random(void)
{
	static uint32_t start_tick = 0;
	static uint32_t aRandom32bit_Note = 0;
	static uint32_t aRandom32bit_Volume = 0;
	static uint32_t aRandom32bit_Repeat = 100;

	if (HAL_GetTick() - start_tick >= 100)//aRandom32bit_Repeat)
	{
		if (aRandom32bit_Note < (NUMBER_OF_NOTES - 1))
			aRandom32bit_Note++;
		else
			aRandom32bit_Note = 1;

		synth_SetImageData(aRandom32bit_Note, 30000);
		synth_SetImageData(aRandom32bit_Note - 1, 0);

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
#pragma GCC pop_options
