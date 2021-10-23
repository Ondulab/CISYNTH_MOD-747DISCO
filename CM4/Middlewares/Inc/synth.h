/*
 * synth.h
 *
 *  Created on: 24 avr. 2019
 *      Author: zhonx
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYNTH_H
#define __SYNTH_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
	IFFT_MODE = 0,
	PLAY_MODE,
}synthModeTypeDef;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
int32_t synth_IfftInit(void);
int32_t synth_GetImageData(uint32_t index);
int32_t synth_SetImageData(uint32_t index, int32_t value);
void synth_AudioProcess(synthModeTypeDef mode);

/* Private defines -----------------------------------------------------------*/

#endif /* __SYNTH_H */
