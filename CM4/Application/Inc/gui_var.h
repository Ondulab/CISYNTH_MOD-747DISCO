/*
 * gui_var.h
 *
 *  Created on: May 31, 2020
 *      Author: zhonx
 */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GUI_VAR_H
#define __GUI_VAR_H

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
struct guiValues {
	int32_t attackSlider;
	int32_t releaseSlider;
};

/* Exported constants --------------------------------------------------------*/
volatile struct guiValues guiValues;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MENU_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
