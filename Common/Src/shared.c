/**
 ******************************************************************************
 * @file           : shared.c
 * @brief          : shared data structure for both cpu
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "shared.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

__attribute__ ((section(".shared_var")))
struct shared_var shared_var;

__attribute__ ((section(".params")))
volatile struct params params;

__attribute__ ((section(".cvdata")))
volatile int32_t cvData[NUMBER_OF_NOTES / IMAGE_WEIGHT];

__attribute__ ((section(".image")))
volatile int32_t imageData[NUMBER_OF_NOTES];

__attribute__ ((section(".audio")))
volatile int16_t audioBuff[AUDIO_BUFFER_SIZE * 4];

__attribute__ ((section(".wave")))
volatile struct wave waves[NUMBER_OF_NOTES];

__attribute__ ((section(".unitary_waveform")))
volatile int16_t unitary_waveform[WAVEFORM_TABLE_SIZE];

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
