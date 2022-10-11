/*
 * gui_var.h
 *
 *  Created on: May 31, 2020
 *      Author: zhonx
 */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GUI_VAR_H
#define __GUI_VAR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
struct guiValues {
	int32_t attackSlider;
	int32_t releaseSlider;
	int32_t commaPerSemitoneSlider;
	int32_t startFreqSlider;
};

/* Exported constants --------------------------------------------------------*/
extern volatile struct guiValues guiValues;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* __GUI_VAR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
