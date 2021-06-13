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
#include "menu.h"
#include "pcm5102.h"

#include "lwip.h"

#include "stdio.h"
#include "stdbool.h"

extern __IO uint32_t synth_process_cnt;
static void cisynth_ifft_SetHint(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
int cisynth_ifft(void)
{
	uint8_t FreqStr[256] = {0};
	uint32_t cis_color = 0;
	static uint32_t start_tick;
	uint32_t latency;
	int32_t i = 0;

	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	synth_IfftInit();

	cisynth_ifft_SetHint();

	//	synth_SetImageData(60, 18000); //for testing
	//	synth_SetImageData(100, 18000); //for testing
	synth_SetImageData(85, 5700);
	//	synth_SetImageData(20, 65000); //for testing
	//	synth_SetImageData(75, 65000);
	//	synth_SetImageData(60, 13000); //for testing
	//	synth_SetImageData(105, 50700);

	while (1)
	{
		start_tick = HAL_GetTick();
		while ((synth_process_cnt) < (SAMPLING_FREQUENCY / DISPLAY_REFRESH_FPS))
		{
			MX_LWIP_Process();
			synth_AudioProcess(IFFT_MODE);
		}

		latency = HAL_GetTick() - start_tick;
		sprintf((char *)FreqStr, "%dHz", (int)((synth_process_cnt * 1000) / latency));
		synth_process_cnt = 0;

		UTIL_LCD_FillRect(0, DISPLAY_AERA1_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_AERAS1_HEIGHT, UTIL_LCD_COLOR_ST_GRAY_DARK);

		//		static uint32_t note = 0;
		//		if (note > NUMBER_OF_NOTES)
		//		{
		//			note = 0;
		//		}

		//		synth_SetImageData(++note, 65000); //for testing
		//		synth_SetImageData(note - 1, 0);

		HAL_Delay(1);
		for (i = 0; i < ((DISPLAY_MAX_X_LENGTH) - 1); i++)
		{
			UTIL_LCD_SetPixel(i, DISPLAY_AERA1_Y1POS + (DISPLAY_AERAS1_HEIGHT / 2) - (pcm5102_GetAudioData(i / 2) / 256), UTIL_LCD_COLOR_WHITE);
		}

		UTIL_LCD_DisplayStringAt(0, 1, (uint8_t*)FreqStr, RIGHT_MODE);

		BSP_LED_Toggle(LED_RED);
	}
}
#pragma GCC pop_options
/**
 * @brief  Display Audio demo hint
 * @param  None
 * @retval None
 */
static void cisynth_ifft_SetHint(void)
{
	/* Set Audio header description */
	UTIL_LCD_FillRect(0, DISPLAY_HEAD_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_HEAD_Y2POS, UTIL_LCD_COLOR_BLACK);
	UTIL_LCD_DisplayStringAt(0, 1, (uint8_t *)"SPECTRAL SYNTH SCANNER 3", CENTER_MODE);
	UTIL_LCD_DisplayStringAt(0, 1, (uint8_t *)"IFFT BW", LEFT_MODE);
}
