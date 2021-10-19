/*
 * synth.c
 *
 *  Created on: 24 avr. 2019
 *      Author: zhonx
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "menu.h"
#include "config.h"
#include "rng.h"

#include "basetypes.h"
#include "arm_math.h"
#include "stdlib.h"
#include "stdio.h"

#include "shared.h"
#include "wave_generation.h"
#include "synth.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static volatile int16_t *unitary_waveform = &__unitary_waveform__;// = NULL;
static struct wave *waves = &__wave__;//[NUMBER_OF_NOTES];

/* Variable containing black and white frame from CIS*/

//static uint16_t imageData[((CIS_END_CAPTURE * CIS_ADC_OUT_LINES) / CIS_IFFT_OVERSAMPLING_RATIO) - 1]; // for debug

/* Private function prototypes -----------------------------------------------*/

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

//	//allocate the contiguous memory area for storage image data
//	imageData = malloc(NUMBER_OF_NOTES * sizeof(int32_t*));
//	if (imageData == NULL)
//	{
//		Error_Handler();
//	}

//	memset(imageData, 0, NUMBER_OF_NOTES * sizeof(int32_t*));

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
	UTIL_LCD_FillRect(0, DISPLAY_AERA3_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_AERAS3_HEIGHT, UTIL_LCD_COLOR_BLACK);
	sprintf((char *)FreqStr, " %d -> %dHz      Octave:%d", (int)waves[0].frequency, (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));
	UTIL_LCD_DisplayStringAt(0, DISPLAY_AERA3_Y1POS, (uint8_t*)FreqStr, LEFT_MODE);

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

	return 0;
}