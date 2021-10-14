/**
 ******************************************************************************
 * @file           : synth_cv.c
 * @brief          : Oled display driver
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include "config.h"
#include "rng.h"
#include "dac.h"
#include "tim.h"

#include "basetypes.h"
#include "arm_math.h"
#include "stdlib.h"
#include "stdio.h"

#include "wave_generation.h"
#include "synth_cv.h"
#include "udp_server.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Variable containing black and white frame from CIS*/
static int32_t *imageData = NULL;
static DAC_ChannelConfTypeDef sConfig;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
static void cisynth_cv_SetHint(void);

/**
 * @brief  The application entry point.
 * @retval int
 */
int32_t cisynth_cv(void)
{
	uint8_t FreqStr[256] = {0};
	static uint32_t start_tick;
	uint8_t last_TRG_state = 0;
	uint32_t latency;
	int32_t i = 0;
	uint32_t tmp_accumulation = 0;
	int32_t cnt = 0;

	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	cisynth_cvInit();

	cisynth_cv_SetHint();

	while (1)
	{
		start_tick = HAL_GetTick();
		while (1)
		{
			MX_LWIP_Process();
			udp_serverReceiveImage(imageData);
			if (HAL_GPIO_ReadPin(ARD_D2_GPIO_Port, ARD_D2_Pin) == TRUE)
			{
				cnt = 0;
			}
			if (HAL_GPIO_ReadPin(ARD_D7_GPIO_Port, ARD_D7_Pin) == TRUE)
			{
				if (last_TRG_state != TRUE)
					cnt += IMAGE_WEIGHT;

				if (cnt > NUMBER_OF_NOTES)
					cnt = 0;

				last_TRG_state = TRUE;
			}
			else
			{
				last_TRG_state = FALSE;
			}
			/*##-5- Set DAC channel1 DHR12RD register ################################################*/

			for (i = 0; i < IMAGE_WEIGHT; i++)
			{
				if ((cnt + i) < NUMBER_OF_NOTES)
					tmp_accumulation += (imageData[cnt + i] >> 4);
			}

			tmp_accumulation /= i;

			if (HAL_DAC_SetValue(&hdac1, DAC1_CHANNEL_1, DAC_ALIGN_12B_R, tmp_accumulation) != HAL_OK)
			{
				/* Setting value Error */
				Error_Handler();
			}
			HAL_Delay(10);
		}

		latency = HAL_GetTick() - start_tick;
		sprintf((char *)FreqStr, "%dHz", (int)((synth_process_cnt * 1000) / latency));
		cnt = 0;

//		UTIL_LCD_FillRect(0, DISPLAY_AERA1_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_AERAS1_HEIGHT, UTIL_LCD_COLOR_ST_GRAY_DARK);

		//		static uint32_t note = 0;
		//		if (note > NUMBER_OF_NOTES)
		//		{
		//			note = 0;
		//		}

		//		synth_SetImageData(++note, 65000); //for testing
		//		synth_SetImageData(note - 1, 0);

		HAL_Delay(1);
		//		for (i = 0; i < ((DISPLAY_MAX_X_LENGTH) - 1); i++)
		//		{
		//			UTIL_LCD_SetPixel(i, DISPLAY_AERA1_Y1POS + (DISPLAY_AERAS1_HEIGHT / 2) - (pcm5102_GetAudioData(i / 2) / 256), UTIL_LCD_COLOR_WHITE);
		//		}

//		UTIL_LCD_DisplayStringAt(0, 1, (uint8_t*)FreqStr, RIGHT_MODE);

		BSP_LED_Toggle(LED_RED);
	}
}

int32_t cisynth_cvInit(void)
{
	printf("-------- SYNTH CV INIT --------\n");
	printf("-------------------------------\n");

	//allocate the contiguous memory area for storage image data
	imageData = malloc(NUMBER_OF_NOTES * sizeof(int32_t*));
	if (imageData == NULL)
	{
		Error_Handler();
	}

	memset(imageData, 0, NUMBER_OF_NOTES * sizeof(int32_t*));

	//	uint8_t FreqStr[256] = {0};
	//	UTIL_LCD_FillRect(0, DISPLAY_AERA2_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_AERAS2_HEIGHT, UTIL_LCD_COLOR_BLACK);
	//	sprintf((char *)FreqStr, " %d -> %dHz      Octave:%d", (int)waves[0].frequency, (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));
	//	UTIL_LCD_DisplayStringAt(0, DISPLAY_AERA2_Y1POS, (uint8_t*)FreqStr, LEFT_MODE);

	//	printf("First note Freq = %dHz\nSize = %d\n", (int)waves[0].frequency, (int)waves[0].area_size);
	//	printf("Last  note Freq = %dHz\nSize = %d\nOctave = %d\n", (int)waves[NUMBER_OF_NOTES - 1].frequency, (int)waves[NUMBER_OF_NOTES - 1].area_size / (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff), (int)sqrt(waves[NUMBER_OF_NOTES - 1].octave_coeff));

	printf("-------------------------------\n");

	TIM_MasterConfigTypeDef sMasterConfig;

	/*##-1- Configure the TIM peripheral #######################################*/
	/* Time base configuration */
	htim6.Instance = TIM6;

	htim6.Init.Period            = 0xF7FF;
	htim6.Init.Prescaler         = 0;
	htim6.Init.ClockDivision     = 0;
	htim6.Init.CounterMode       = TIM_COUNTERMODE_UP;
	htim6.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim6);

	/* TIM6 TRGO selection */
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig);

	/*##-2- Enable TIM peripheral counter ######################################*/
	HAL_TIM_Base_Start(&htim6);

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

	return 0;
}

/**
 * @brief  Display Audio demo hint
 * @param  None
 * @retval None
 */
static void cisynth_cv_SetHint(void)
{
//	/* Set Audio header description */
//	UTIL_LCD_FillRect(0, DISPLAY_HEAD_Y1POS, DISPLAY_MAX_X_LENGTH, DISPLAY_HEAD_Y2POS, UTIL_LCD_COLOR_BLACK);
//	UTIL_LCD_DisplayStringAt(0, 1, (uint8_t *)"SPECTRAL SYNTH SCANNER 3", CENTER_MODE);
//	UTIL_LCD_DisplayStringAt(0, 1, (uint8_t *)"IFFT BW", LEFT_MODE);
}
