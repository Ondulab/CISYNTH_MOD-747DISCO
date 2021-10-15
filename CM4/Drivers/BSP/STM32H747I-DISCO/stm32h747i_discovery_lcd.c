/**
 ******************************************************************************
 * @file    stm32h747i_discovery_lcd.c
 * @author  MCD Application Team
 * @brief   This file includes the driver for Liquid Crystal Display (LCD) module
 *          mounted on STM32H747I_DISCO board.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/*  How To use this driver:
  --------------------------
   - This driver is used to drive directly a LCD TFT using the DSI interface.
     The following IPs are implied : DSI Host IP block working in conjunction to the
	 LTDC controller.
   - This driver is linked by construction to LCD KoD mounted on MB1166 daughter board.
   - This driver is also used to drive monitors using HDMI interface.

  Driver description:
  ---------------------
   + Initialization steps:
     o Initialize the LCD in default mode using the BSP_LCD_Init() function with the
       following settings:
        - DSI is configured in video mode
        - Pixelformat : LCD_PIXEL_FORMAT_RBG888
        - Orientation : LCD_ORIENTATION_LANDSCAPE.
        - Width       : LCD_DEFAULT_WIDTH (800)
        - Height      : LCD_DEFAULT_HEIGHT(480)
       The default LTDC layer configured is layer 0.
       BSP_LCD_Init() includes DSI, LTDC, LTDC Layer and clock configurations by calling:
        - MX_LTDC_ClockConfig()
        - MX_LTDC_Init()
        - MX_DSIHOST_DSI_Init()
        - MX_LTDC_ConfigLayer()

     o Initialize the LCD with required parameters using the BSP_LCD_InitEx() function.
       To initialize DSI in command mode, user have to override MX_DSIHOST_DSI_Init(), weak function,
       content at application level.

     o Initialize the display with HDMI using BSP_LCD_InitHDMI(). Two display formats
       are supported: HDMI_FORMAT_720_480 or HDMI_FORMAT_720_576

     o Select the LCD layer to be used using the BSP_LCD_SelectLayer() function.
     o Enable the LCD display using the BSP_LCD_DisplayOn() function.
     o Disable the LCD display using the BSP_LCD_DisplayOff() function.
     o Set the display brightness using the BSP_LCD_SetBrightness() function.
     o Get the display brightness using the BSP_LCD_GetBrightness() function.
     o Write a pixel to the LCD memory using the BSP_LCD_WritePixel() function.
     o Read a pixel from the LCD memory using the BSP_LCD_ReadPixel() function.
     o Draw an horizontal line using the BSP_LCD_DrawHLine() function.
     o Draw a vertical line using the BSP_LCD_DrawVLine() function.
     o Draw a bitmap image using the BSP_LCD_DrawBitmap() function.

   + Options
     o Configure the LTDC reload mode by calling BSP_LCD_Relaod(). By default, the
       reload mode is set to BSP_LCD_RELOAD_IMMEDIATE then LTDC is reloaded immediately.
       To control the reload mode:
         - Call BSP_LCD_Relaod() with ReloadType parameter set to BSP_LCD_RELOAD_NONE
         - Configure LTDC (color keying, transparency ..)
         - Call BSP_LCD_Relaod() with ReloadType parameter set to BSP_LCD_RELOAD_IMMEDIATE
           for immediate reload or BSP_LCD_RELOAD_VERTICAL_BLANKING for LTDC reload
           in the next vertical blanking
     o Configure LTDC layers using BSP_LCD_ConfigLayer()
     o Control layer visibility using BSP_LCD_SetLayerVisible()
     o Configure and enable the color keying functionality using the
       BSP_LCD_SetColorKeying() function.
     o Disable the color keying functionality using the BSP_LCD_ResetColorKeying() function.
     o Modify on the fly the transparency and/or the frame buffer address
       using the following functions:
       - BSP_LCD_SetTransparency()
       - BSP_LCD_SetLayerAddress()

   + Display on LCD
     o To draw and fill a basic shapes (dot, line, rectangle, circle, ellipse, .. bitmap)
       on LCD and display text, utility basic_gui.c/.h must be called. Once the LCD is initialized,
       user should call GUI_SetFuncDriver() API to link board LCD drivers to BASIC GUI LCD drivers.
       The basic gui services, defined in basic_gui utility, are ready for use.

  Note:
  --------
    Regarding the "Instance" parameter, needed for all functions, it is used to select
    an LCD instance. On the STM32H747I_DISCO board, there's one instance. Then, this
    parameter should be 0.
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32h747i_discovery_lcd.h"
#include "stm32h747i_discovery_bus.h"
#include "stm32h747i_discovery_sdram.h"

#include "dsihost.h"
#include "ltdc.h"
#include "dma2d.h"
/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32H747I_DISCO
 * @{
 */

/** @defgroup STM32H747I_DISCO_LCD LCD
 * @{
 */
/** @defgroup STM32H747I_DISCO_LCD_Private_Variables Private Variables
 * @{
 */
static LCD_Drv_t                *Lcd_Drv = NULL;
/**
 * @}
 */

/** @defgroup STM32H747I_DISCO_LCD_Private_TypesDefinitions Private TypesDefinitions
 * @{
 */
const LCD_UTILS_Drv_t LCD_Driver =
{
		BSP_LCD_DrawBitmap,
		BSP_LCD_FillRGBRect,
		BSP_LCD_DrawHLine,
		BSP_LCD_DrawVLine,
		BSP_LCD_FillRect,
		BSP_LCD_ReadPixel,
		BSP_LCD_WritePixel,
		BSP_LCD_GetXSize,
		BSP_LCD_GetYSize,
		BSP_LCD_SetActiveLayer,
		BSP_LCD_GetPixelFormat
};

typedef struct
{
	uint32_t      HACT;
	uint32_t      VACT;
	uint32_t      HSYNC;
	uint32_t      HBP;
	uint32_t      HFP;
	uint32_t      VSYNC;
	uint32_t      VBP;
	uint32_t      VFP;

	/* Configure the D-PHY Timings */
	uint32_t      ClockLaneHS2LPTime;
	uint32_t      ClockLaneLP2HSTime;
	uint32_t      DataLaneHS2LPTime;
	uint32_t      DataLaneLP2HSTime;
	uint32_t      DataLaneMaxReadTime;
	uint32_t      StopWaitTime;
} LCD_HDMI_Timing_t;
/**
 * @}
 */

/** @defgroup STM32H747I_DISCO_LCD_Exported_Variables Exported Variables
 * @{
 */
void                *Lcd_CompObj = NULL;
//DSI_HandleTypeDef   hdsi;
//DMA2D_HandleTypeDef hdma2d;
//LTDC_HandleTypeDef  hltdc;
BSP_LCD_Ctx_t       Lcd_Ctx[LCD_INSTANCES_NBR];
/**
 * @}
 */

/** @defgroup STM32H747I_DISCO_LCD_Private_FunctionPrototypes Private FunctionPrototypes
 * @{
 */
static int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size);
static int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size);

#if (USE_LCD_CTRL_OTM8009A > 0)
static int32_t OTM8009A_Probe(uint32_t ColorCoding, uint32_t Orientation);
# endif /* USE_LCD_CTRL_OTM8009A > 0 */

static void LL_FillBuffer(uint32_t Instance, uint32_t *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t Color);
static void LL_ConvertLineToRGB(uint32_t Instance, uint32_t *pSrc, uint32_t *pDst, uint32_t xSize, uint32_t ColorMode);
static void LCD_InitSequence(void);
static void LCD_DeInitSequence(void);
/**
 * @}
 */
/** @defgroup STM32H747I_DISCO_LCD_Private_Macros Private Macros
 * @{
 */
#define CONVERTRGB5652ARGB8888(Color)((((((((Color) >> (11U)) & 0x1FU) * 527U) + 23U) >> (6U)) << (16U)) |\
		(((((((Color) >> (5U)) & 0x3FU) * 259U) + 33U) >> (6U)) << (8U)) |\
		(((((Color) & 0x1FU) * 527U) + 23U) >> (6U)) | (0xFF000000U))

/**
 * @}
 */
/** @defgroup STM32H747I_DISCO_LCD_Exported_Functions LCD Exported Functions
 * @{
 */
/**
 * @brief  Initializes the LCD in default mode.
 * @param  Instance    LCD Instance
 * @param  Orientation LCD_ORIENTATION_PORTRAIT or LCD_ORIENTATION_LANDSCAPE
 * @retval BSP status
 */
int32_t BSP_LCD_Init(uint32_t Instance, uint32_t Orientation)
{
	int32_t ret = BSP_ERROR_NONE;

	Lcd_Ctx[Instance].BppFactor = 2U;

	/* Store pixel format, xsize and ysize information */
	Lcd_Ctx[Instance].PixelFormat = LCD_PIXEL_FORMAT_RGB565;
	Lcd_Ctx[Instance].XSize  = LCD_DEFAULT_WIDTH;
	Lcd_Ctx[Instance].YSize  = LCD_DEFAULT_HEIGHT;

	/* Toggle Hardware Reset of the LCD using its XRES signal (active low) */
	BSP_LCD_Reset(Instance);

	/* Initialize LCD special pins GPIOs */
	LCD_InitSequence();

	if(ret == BSP_ERROR_NONE)
	{
		/* Before configuring LTDC layer, ensure SDRAM is initialized */
#if !defined(DATA_IN_ExtSDRAM)
		/* Initialize the SDRAM */
		if(BSP_SDRAM_Init(0) != BSP_ERROR_NONE)
		{
			return BSP_ERROR_PERIPH_FAILURE;
		}
#endif /* DATA_IN_ExtSDRAM */

		/* Enable the DSI host and wrapper after the LTDC initialization
        To avoid any synchronization issue, the DSI shall be started after enabling the LTDC */
		(void)HAL_DSI_Start(&hdsi);

		/* Enable the DSI BTW for read operations */
		(void)HAL_DSI_ConfigFlowControl(&hdsi, DSI_FLOW_CONTROL_BTA);

#if (USE_LCD_CTRL_OTM8009A == 1)
		/* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver)
        depending on configuration of DSI */
		if(OTM8009A_Probe(LCD_PIXEL_FORMAT_RGB565, Orientation) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_UNKNOWN_COMPONENT;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
#endif
		//		}
		/* By default the reload is activated and executed immediately */
		Lcd_Ctx[Instance].ReloadEnable = 1U;
	}


	return ret;
}

/**
 * @brief  BSP LCD Reset
 *         Hw reset the LCD DSI activating its XRES signal (active low for some time)
 *         and deactivating it later.
 * @param  Instance LCD Instance
 */
void BSP_LCD_Reset(uint32_t Instance)
{
	GPIO_InitTypeDef  gpio_init_structure;

	LCD_RESET_GPIO_CLK_ENABLE();

	/* Configure the GPIO Reset pin */
	gpio_init_structure.Pin   = LCD_RESET_PIN;
	gpio_init_structure.Mode  = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull  = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(LCD_RESET_GPIO_PORT , &gpio_init_structure);

	/* Activate XRES active low */
	HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT , LCD_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(20);/* wait 20 ms */
	HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT , LCD_RESET_PIN, GPIO_PIN_SET);/* Deactivate XRES */
	HAL_Delay(10);/* Wait for 10ms after releasing XRES before sending commands */
}

/**
 * @brief  Configure LCD control pins (Back-light, Display Enable and TE)
 * @retval None
 */
static void LCD_InitSequence(void)
{
	GPIO_InitTypeDef  gpio_init_structure;

	/* LCD_BL_CTRL GPIO configuration */
	LCD_BL_CTRL_GPIO_CLK_ENABLE();

	gpio_init_structure.Pin       = LCD_BL_CTRL_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;
	gpio_init_structure.Pull      = GPIO_NOPULL;

	HAL_GPIO_Init(LCD_BL_CTRL_GPIO_PORT, &gpio_init_structure);
	/* Assert back-light LCD_BL_CTRL pin */
	HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_PORT, LCD_BL_CTRL_PIN, GPIO_PIN_SET);

	/* LCD_TE_CTRL GPIO configuration */
	LCD_TE_GPIO_CLK_ENABLE();

	gpio_init_structure.Pin       = LCD_TE_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_INPUT;
	gpio_init_structure.Speed     = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(LCD_TE_GPIO_PORT, &gpio_init_structure);
	/* Assert back-light LCD_BL_CTRL pin */
	HAL_GPIO_WritePin(LCD_TE_GPIO_PORT, LCD_TE_PIN, GPIO_PIN_SET);

	/** @brief NVIC configuration for LTDC interrupt that is now enabled */
	HAL_NVIC_SetPriority(LTDC_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(LTDC_IRQn);

	/** @brief NVIC configuration for DMA2D interrupt that is now enabled */
	HAL_NVIC_SetPriority(DMA2D_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DMA2D_IRQn);

	/** @brief NVIC configuration for DSI interrupt that is now enabled */
	HAL_NVIC_SetPriority(DSI_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DSI_IRQn);
}

/**
 * @brief  DeInitializes LCD GPIO special pins MSP.
 * @retval None
 */
static void LCD_DeInitSequence(void)
{
	GPIO_InitTypeDef  gpio_init_structure;

	/* LCD_BL_CTRL GPIO configuration */
	/* LCD_BL_CTRL GPIO deactivation */
	gpio_init_structure.Pin       = LCD_BL_CTRL_PIN;
	HAL_GPIO_DeInit(LCD_BL_CTRL_GPIO_PORT, gpio_init_structure.Pin);

	/* LCD_TE_CTRL GPIO configuration */
}

/**
 * @brief  MX LTDC layer configuration.
 * @param  hltdc      LTDC handle
 * @param  LayerIndex Layer 0 or 1
 * @param  Config     Layer configuration
 * @retval HAL status
 */
__weak HAL_StatusTypeDef MX_LTDC_ConfigLayer(LTDC_HandleTypeDef *hltdc, uint32_t LayerIndex, MX_LTDC_LayerConfig_t *Config)
{
	LTDC_LayerCfgTypeDef pLayerCfg;

	pLayerCfg.WindowX0 = Config->X0;
	pLayerCfg.WindowX1 = Config->X1;
	pLayerCfg.WindowY0 = Config->Y0;
	pLayerCfg.WindowY1 = Config->Y1;
	pLayerCfg.PixelFormat = Config->PixelFormat;
	pLayerCfg.Alpha = 255;
	pLayerCfg.Alpha0 = 0;
	pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	pLayerCfg.FBStartAdress = Config->Address;
	pLayerCfg.ImageWidth = (Config->X1 - Config->X0);
	pLayerCfg.ImageHeight = (Config->Y1 - Config->Y0);
	pLayerCfg.Backcolor.Blue = 0;
	pLayerCfg.Backcolor.Green = 0;
	pLayerCfg.Backcolor.Red = 0;
	return HAL_LTDC_ConfigLayer(hltdc, &pLayerCfg, LayerIndex);
}

/**
 * @brief  LTDC layer configuration.
 * @param  Instance   LCD instance
 * @param  LayerIndex Layer 0 or 1
 * @param  Config     Layer configuration
 * @retval HAL status
 */
int32_t BSP_LCD_ConfigLayer(uint32_t Instance, uint32_t LayerIndex, BSP_LCD_LayerConfig_t *Config)
{
	int32_t ret = BSP_ERROR_NONE;
	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if (MX_LTDC_ConfigLayer(&hltdc, LayerIndex, Config) != HAL_OK)
		{
			ret = BSP_ERROR_PERIPH_FAILURE;
		}
	}
	return ret;
}

/**
 * @brief  Set the LCD Active Layer.
 * @param  Instance    LCD Instance
 * @param  LayerIndex  LCD layer index
 * @retval BSP status
 */
int32_t BSP_LCD_SetActiveLayer(uint32_t Instance, uint32_t LayerIndex)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		Lcd_Ctx[Instance].ActiveLayer = LayerIndex;
	}

	return ret;
}
/**
 * @brief  Gets the LCD Active LCD Pixel Format.
 * @param  Instance    LCD Instance
 * @param  PixelFormat Active LCD Pixel Format
 * @retval BSP status
 */
int32_t BSP_LCD_GetPixelFormat(uint32_t Instance, uint32_t *PixelFormat)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		/* Only RGB565 format is supported */
		*PixelFormat = Lcd_Ctx[Instance].PixelFormat;
	}

	return ret;
}
/**
 * @brief  Control the LTDC reload
 * @param  Instance    LCD Instance
 * @param  ReloadType can be one of the following values
 *         - BSP_LCD_RELOAD_NONE
 *         - BSP_LCD_RELOAD_IMMEDIATE
 *         - BSP_LCD_RELOAD_VERTICAL_BLANKING
 * @retval BSP status
 */
int32_t BSP_LCD_Relaod(uint32_t Instance, uint32_t ReloadType)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else if(ReloadType == BSP_LCD_RELOAD_NONE)
	{
		Lcd_Ctx[Instance].ReloadEnable = 0U;
	}
	else if(HAL_LTDC_Reload (&hltdc, ReloadType) != HAL_OK)
	{
		ret = BSP_ERROR_PERIPH_FAILURE;
	}
	else
	{
		Lcd_Ctx[Instance].ReloadEnable = 1U;
	}

	return ret;
}

/**
 * @brief  Sets an LCD Layer visible
 * @param  Instance    LCD Instance
 * @param  LayerIndex  Visible Layer
 * @param  State  New state of the specified layer
 *          This parameter can be one of the following values:
 *            @arg  ENABLE
 *            @arg  DISABLE
 * @retval BSP status
 */
int32_t BSP_LCD_SetLayerVisible(uint32_t Instance, uint32_t LayerIndex, FunctionalState State)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(State == ENABLE)
		{
			__HAL_LTDC_LAYER_ENABLE(&hltdc, LayerIndex);
		}
		else
		{
			__HAL_LTDC_LAYER_DISABLE(&hltdc, LayerIndex);
		}

		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			__HAL_LTDC_RELOAD_IMMEDIATE_CONFIG(&hltdc);
		}
	}

	return ret;
}

/**
 * @brief  Configures the transparency.
 * @param  Instance      LCD Instance
 * @param  LayerIndex    Layer foreground or background.
 * @param  Transparency  Transparency
 *           This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFF
 * @retval BSP status
 */
int32_t BSP_LCD_SetTransparency(uint32_t Instance, uint32_t LayerIndex, uint8_t Transparency)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			(void)HAL_LTDC_SetAlpha(&hltdc, Transparency, LayerIndex);
		}
		else
		{
			(void)HAL_LTDC_SetAlpha_NoReload(&hltdc, Transparency, LayerIndex);
		}
	}

	return ret;
}

/**
 * @brief  Sets an LCD layer frame buffer address.
 * @param  Instance    LCD Instance
 * @param  LayerIndex  Layer foreground or background
 * @param  Address     New LCD frame buffer value
 * @retval BSP status
 */
int32_t BSP_LCD_SetLayerAddress(uint32_t Instance, uint32_t LayerIndex, uint32_t Address)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			(void)HAL_LTDC_SetAddress(&hltdc, Address, LayerIndex);
		}
		else
		{
			(void)HAL_LTDC_SetAddress_NoReload(&hltdc, Address, LayerIndex);
		}
	}

	return ret;
}

/**
 * @brief  Sets display window.
 * @param  Instance    LCD Instance
 * @param  LayerIndex  Layer index
 * @param  Xpos   LCD X position
 * @param  Ypos   LCD Y position
 * @param  Width  LCD window width
 * @param  Height LCD window height
 * @retval BSP status
 */
int32_t BSP_LCD_SetLayerWindow(uint32_t Instance, uint16_t LayerIndex, uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			/* Reconfigure the layer size  and position */
			(void)HAL_LTDC_SetWindowSize(&hltdc, Width, Height, LayerIndex);
			(void)HAL_LTDC_SetWindowPosition(&hltdc, Xpos, Ypos, LayerIndex);
		}
		else
		{
			/* Reconfigure the layer size and position */
			(void)HAL_LTDC_SetWindowSize_NoReload(&hltdc, Width, Height, LayerIndex);
			(void)HAL_LTDC_SetWindowPosition_NoReload(&hltdc, Xpos, Ypos, LayerIndex);
		}

		Lcd_Ctx[Instance].XSize = Width;
		Lcd_Ctx[Instance].YSize = Height;
	}

	return ret;
}

/**
 * @brief  Configures and sets the color keying.
 * @param  Instance    LCD Instance
 * @param  LayerIndex  Layer foreground or background
 * @param  Color       Color reference
 * @retval BSP status
 */
int32_t BSP_LCD_SetColorKeying(uint32_t Instance, uint32_t LayerIndex, uint32_t Color)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			/* Configure and Enable the color Keying for LCD Layer */
			(void)HAL_LTDC_ConfigColorKeying(&hltdc, Color, LayerIndex);
			(void)HAL_LTDC_EnableColorKeying(&hltdc, LayerIndex);
		}
		else
		{
			/* Configure and Enable the color Keying for LCD Layer */
			(void)HAL_LTDC_ConfigColorKeying_NoReload(&hltdc, Color, LayerIndex);
			(void)HAL_LTDC_EnableColorKeying_NoReload(&hltdc, LayerIndex);
		}
	}
	return ret;
}

/**
 * @brief  Disables the color keying.
 * @param  Instance    LCD Instance
 * @param  LayerIndex Layer foreground or background
 * @retval BSP status
 */
int32_t BSP_LCD_ResetColorKeying(uint32_t Instance, uint32_t LayerIndex)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Ctx[Instance].ReloadEnable == 1U)
		{
			/* Disable the color Keying for LCD Layer */
			(void)HAL_LTDC_DisableColorKeying(&hltdc, LayerIndex);
		}
		else
		{
			/* Disable the color Keying for LCD Layer */
			(void)HAL_LTDC_DisableColorKeying_NoReload(&hltdc, LayerIndex);
		}
	}

	return ret;
}

/**
 * @brief  Gets the LCD X size.
 * @param  Instance  LCD Instance
 * @param  XSize     LCD width
 * @retval BSP status
 */
int32_t BSP_LCD_GetXSize(uint32_t Instance, uint32_t *XSize)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else if(Lcd_Drv->GetXSize != NULL)
	{
		*XSize = Lcd_Ctx[Instance].XSize;
	}

	return ret;
}

/**
 * @brief  Gets the LCD Y size.
 * @param  Instance  LCD Instance
 * @param  YSize     LCD Height
 * @retval BSP status
 */
int32_t BSP_LCD_GetYSize(uint32_t Instance, uint32_t *YSize)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else if(Lcd_Drv->GetYSize != NULL)
	{
		*YSize = Lcd_Ctx[Instance].YSize;
	}

	return ret;
}

/**
 * @brief  Switch On the display.
 * @param  Instance    LCD Instance
 * @retval BSP status
 */
int32_t BSP_LCD_DisplayOn(uint32_t Instance)
{
	int32_t ret;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Drv->DisplayOn(Lcd_CompObj) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_PERIPH_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
	}

	return ret;
}

/**
 * @brief  Switch Off the display.
 * @param  Instance    LCD Instance
 * @retval BSP status
 */
int32_t BSP_LCD_DisplayOff(uint32_t Instance)
{
	int32_t ret;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Drv->DisplayOff(Lcd_CompObj) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_PERIPH_FAILURE;
		}
		else
		{
			ret = BSP_ERROR_NONE;
		}
	}

	return ret;
}

/**
 * @brief  Set the brightness value
 * @param  Instance    LCD Instance
 * @param  Brightness [00: Min (black), 100 Max]
 * @retval BSP status
 */
int32_t BSP_LCD_SetBrightness(uint32_t Instance, uint32_t Brightness)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Drv->SetBrightness(Lcd_CompObj, Brightness) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_PERIPH_FAILURE;
		}
	}

	return ret;
}

/**
 * @brief  Set the brightness value
 * @param  Instance    LCD Instance
 * @param  Brightness [00: Min (black), 100 Max]
 * @retval BSP status
 */
int32_t BSP_LCD_GetBrightness(uint32_t Instance, uint32_t *Brightness)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Instance >= LCD_INSTANCES_NBR)
	{
		ret = BSP_ERROR_WRONG_PARAM;
	}
	else
	{
		if(Lcd_Drv->GetBrightness(Lcd_CompObj, Brightness) != BSP_ERROR_NONE)
		{
			ret = BSP_ERROR_PERIPH_FAILURE;
		}
	}

	return ret;
}

/**
 * @brief  Draws a bitmap picture loaded in the internal Flash in currently active layer.
 * @param  Instance LCD Instance
 * @param  Xpos Bmp X position in the LCD
 * @param  Ypos Bmp Y position in the LCD
 * @param  pBmp Pointer to Bmp picture address in the internal Flash.
 * @retval BSP status
 */
int32_t BSP_LCD_DrawBitmap(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint8_t *pBmp)
{
	int32_t ret = BSP_ERROR_NONE;
	uint32_t index, width, height, bit_pixel;
	uint32_t Address;
	uint32_t input_color_mode;
	uint8_t *pbmp;

	/* Get bitmap data address offset */
	index = (uint32_t)pBmp[10] + ((uint32_t)pBmp[11] << 8) + ((uint32_t)pBmp[12] << 16)  + ((uint32_t)pBmp[13] << 24);

	/* Read bitmap width */
	width = (uint32_t)pBmp[18] + ((uint32_t)pBmp[19] << 8) + ((uint32_t)pBmp[20] << 16)  + ((uint32_t)pBmp[21] << 24);

	/* Read bitmap height */
	height = (uint32_t)pBmp[22] + ((uint32_t)pBmp[23] << 8) + ((uint32_t)pBmp[24] << 16)  + ((uint32_t)pBmp[25] << 24);

	/* Read bit/pixel */
	bit_pixel = (uint32_t)pBmp[28] + ((uint32_t)pBmp[29] << 8);

	/* Set the address */
	Address = hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (((Lcd_Ctx[Instance].XSize*Ypos) + Xpos)*Lcd_Ctx[Instance].BppFactor);

	/* Get the layer pixel format */
	if ((bit_pixel/8U) == 4U)
	{
		input_color_mode = DMA2D_INPUT_ARGB8888;
	}
	else if ((bit_pixel/8U) == 2U)
	{
		input_color_mode = DMA2D_INPUT_RGB565;
	}
	else
	{
		input_color_mode = DMA2D_INPUT_RGB888;
	}

	/* Bypass the bitmap header */
	pbmp = pBmp + (index + (width * (height - 1U) * (bit_pixel/8U)));

	/* Convert picture to ARGB8888 pixel format */
	for(index=0; index < height; index++)
	{
		/* Pixel format conversion */
		LL_ConvertLineToRGB(Instance, (uint32_t *)pbmp, (uint32_t *)Address, width, input_color_mode);

		/* Increment the source and destination buffers */
		Address+=  (Lcd_Ctx[Instance].XSize * Lcd_Ctx[Instance].BppFactor);
		pbmp -= width*(bit_pixel/8U);
	}

	return ret;
}
/**
 * @brief  Draw a horizontal line on LCD.
 * @param  Instance LCD Instance.
 * @param  Xpos X position.
 * @param  Ypos Y position.
 * @param  pData Pointer to RGB line data
 * @param  Width Rectangle width.
 * @param  Height Rectangle Height.
 * @retval BSP status.
 */
int32_t BSP_LCD_FillRGBRect(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint8_t *pData, uint32_t Width, uint32_t Height)
{
	uint32_t i;

#if (USE_DMA2D_TO_FILL_RGB_RECT == 1)
	uint32_t  Xaddress;
	for(i = 0; i < Height; i++)
	{
		/* Get the line address */
		Xaddress = hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (Lcd_Ctx[Instance].BppFactor*(((Lcd_Ctx[Instance].XSize + i)*Ypos) + Xpos));

		/* Write line */
		if(Lcd_Ctx[Instance].PixelFormat == LCD_PIXEL_FORMAT_RGB565)
		{
			LL_ConvertLineToRGB(Instance, (uint32_t *)pData, (uint32_t *)Xaddress, Width, DMA2D_INPUT_RGB565);
		}
		else
		{
			LL_ConvertLineToRGB(Instance, (uint32_t *)pData, (uint32_t *)Xaddress, Width, DMA2D_INPUT_ARGB8888);
		}
		pData += Lcd_Ctx[Instance].BppFactor*Width;
	}
#else
	uint32_t color, j;
	for(i = 0; i < Height; i++)
	{
		for(j = 0; j < Width; j++)
		{
			color = *pData | (*(pData + 1) << 8) | (*(pData + 2) << 16) | (*(pData + 3) << 24);
			BSP_LCD_WritePixel(Instance, Xpos + j, Ypos + i, color);
			pData += Lcd_Ctx[Instance].BppFactor;
		}
	}
#endif
	return BSP_ERROR_NONE;
}

/**
 * @brief  Draws an horizontal line in currently active layer.
 * @param  Instance   LCD Instance
 * @param  Xpos  X position
 * @param  Ypos  Y position
 * @param  Length  Line length
 * @param  Color Pixel color
 * @retval BSP status.
 */
int32_t BSP_LCD_DrawHLine(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
	uint32_t  Xaddress;

	/* Get the line address */
	Xaddress = hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (Lcd_Ctx[Instance].BppFactor*((Lcd_Ctx[Instance].XSize*Ypos) + Xpos));

	/* Write line */
	if((Xpos + Length) > Lcd_Ctx[Instance].XSize)
	{
		Length = Lcd_Ctx[Instance].XSize - Xpos;
	}
	LL_FillBuffer(Instance, (uint32_t *)Xaddress, Length, 1, 0, Color);

	return BSP_ERROR_NONE;
}

/**
 * @brief  Draws a vertical line in currently active layer.
 * @param  Instance   LCD Instance
 * @param  Xpos  X position
 * @param  Ypos  Y position
 * @param  Length  Line length
 * @param  Color Pixel color
 * @retval BSP status.
 */
int32_t BSP_LCD_DrawVLine(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Length, uint32_t Color)
{
	uint32_t  Xaddress;

	/* Get the line address */
	Xaddress = (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress) + (Lcd_Ctx[Instance].BppFactor*(Lcd_Ctx[Instance].XSize*Ypos + Xpos));

	/* Write line */
	if((Ypos + Length) > Lcd_Ctx[Instance].YSize)
	{
		Length = Lcd_Ctx[Instance].YSize - Ypos;
	}
	LL_FillBuffer(Instance, (uint32_t *)Xaddress, 1, Length, (Lcd_Ctx[Instance].XSize - 1U), Color);

	return BSP_ERROR_NONE;
}

/**
 * @brief  Draws a full rectangle in currently active layer.
 * @param  Instance   LCD Instance
 * @param  Xpos X position
 * @param  Ypos Y position
 * @param  Width Rectangle width
 * @param  Height Rectangle height
 * @param  Color Pixel color
 * @retval BSP status.
 */
int32_t BSP_LCD_FillRect(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Width, uint32_t Height, uint32_t Color)
{
	uint32_t  Xaddress;

	/* Get the rectangle start address */
	Xaddress = (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress) + (Lcd_Ctx[Instance].BppFactor*(Lcd_Ctx[Instance].XSize*Ypos + Xpos));

	/* Fill the rectangle */
	LL_FillBuffer(Instance, (uint32_t *)Xaddress, Width, Height, (Lcd_Ctx[Instance].XSize - Width), Color);

	return BSP_ERROR_NONE;
}

/**
 * @brief  Reads an LCD pixel.
 * @param  Instance    LCD Instance
 * @param  Xpos X position
 * @param  Ypos Y position
 * @param  Color RGB pixel color
 * @retval BSP status
 */
int32_t BSP_LCD_ReadPixel(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t *Color)
{
	if(hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
	{
		/* Read data value from SDRAM memory */
		*Color = *(__IO uint32_t*) (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (4U*(Ypos*Lcd_Ctx[Instance].XSize + Xpos)));
	}
	else /* if((hltdc.LayerCfg[layer].PixelFormat == LTDC_PIXEL_FORMAT_RGB565) */
	{
		/* Read data value from SDRAM memory */
		*Color = *(__IO uint16_t*) (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (2U*(Ypos*Lcd_Ctx[Instance].XSize + Xpos)));
	}

	return BSP_ERROR_NONE;
}

/**
 * @brief  Draws a pixel on LCD.
 * @param  Instance    LCD Instance
 * @param  Xpos X position
 * @param  Ypos Y position
 * @param  Color Pixel color
 * @retval BSP status
 */
int32_t BSP_LCD_WritePixel(uint32_t Instance, uint32_t Xpos, uint32_t Ypos, uint32_t Color)
{
	if(hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].PixelFormat == LTDC_PIXEL_FORMAT_ARGB8888)
	{
		/* Write data value to SDRAM memory */
		*(__IO uint32_t*) (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (4U*(Ypos*Lcd_Ctx[Instance].XSize + Xpos))) = Color;
	}
	else
	{
		/* Write data value to SDRAM memory */
		*(__IO uint16_t*) (hltdc.LayerCfg[Lcd_Ctx[Instance].ActiveLayer].FBStartAdress + (2U*(Ypos*Lcd_Ctx[Instance].XSize + Xpos))) = Color;
	}

	return BSP_ERROR_NONE;
}

/**
 * @}
 */

/** @defgroup STM32H747I_DISCO_LCD_Private_Functions Private Functions
 * @{
 */
/**
 * @brief  Fills a buffer.
 * @param  Instance LCD Instance
 * @param  pDst Pointer to destination buffer
 * @param  xSize Buffer width
 * @param  ySize Buffer height
 * @param  OffLine Offset
 * @param  Color Color index
 */
static void LL_FillBuffer(uint32_t Instance, uint32_t *pDst, uint32_t xSize, uint32_t ySize, uint32_t OffLine, uint32_t Color)
{
	uint32_t output_color_mode, input_color = Color;

	switch(Lcd_Ctx[Instance].PixelFormat)
	{
	case LCD_PIXEL_FORMAT_RGB565:
		output_color_mode = DMA2D_OUTPUT_RGB565; /* RGB565 */
		input_color = CONVERTRGB5652ARGB8888(Color);
		break;
	case LCD_PIXEL_FORMAT_RGB888:
	default:
		output_color_mode = DMA2D_OUTPUT_ARGB8888; /* ARGB8888 */
		break;
	}

	/* Register to memory mode with ARGB8888 as color Mode */
	hdma2d.Init.Mode         = DMA2D_R2M;
	hdma2d.Init.ColorMode    = output_color_mode;
	hdma2d.Init.OutputOffset = OffLine;

	hdma2d.Instance = DMA2D;

	/* DMA2D Initialization */
	if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
	{
		if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
		{
			if (HAL_DMA2D_Start(&hdma2d, input_color, (uint32_t)pDst, xSize, ySize) == HAL_OK)
			{
				/* Polling For DMA transfer */
				(void)HAL_DMA2D_PollForTransfer(&hdma2d, 25);
			}
		}
	}
}

/**
 * @brief  Converts a line to an RGB pixel format.
 * @param  Instance LCD Instance
 * @param  pSrc Pointer to source buffer
 * @param  pDst Output color
 * @param  xSize Buffer width
 * @param  ColorMode Input color mode
 */
static void LL_ConvertLineToRGB(uint32_t Instance, uint32_t *pSrc, uint32_t *pDst, uint32_t xSize, uint32_t ColorMode)
{
	uint32_t output_color_mode;

	switch(Lcd_Ctx[Instance].PixelFormat)
	{
	case LCD_PIXEL_FORMAT_RGB565:
		output_color_mode = DMA2D_OUTPUT_RGB565; /* RGB565 */
		break;
	case LCD_PIXEL_FORMAT_RGB888:
	default:
		output_color_mode = DMA2D_OUTPUT_ARGB8888; /* ARGB8888 */
		break;
	}

	/* Configure the DMA2D Mode, Color Mode and output offset */
	hdma2d.Init.Mode         = DMA2D_M2M_PFC;
	hdma2d.Init.ColorMode    = output_color_mode;
	hdma2d.Init.OutputOffset = 0;

	/* Foreground Configuration */
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputAlpha = 0xFF;
	hdma2d.LayerCfg[1].InputColorMode = ColorMode;
	hdma2d.LayerCfg[1].InputOffset = 0;

	hdma2d.Instance = DMA2D;

	/* DMA2D Initialization */
	if(HAL_DMA2D_Init(&hdma2d) == HAL_OK)
	{
		if(HAL_DMA2D_ConfigLayer(&hdma2d, 1) == HAL_OK)
		{
			if (HAL_DMA2D_Start(&hdma2d, (uint32_t)pSrc, (uint32_t)pDst, xSize, 1) == HAL_OK)
			{
				/* Polling For DMA transfer */
				(void)HAL_DMA2D_PollForTransfer(&hdma2d, 50);
			}
		}
	}
}

/**
 * @brief  DCS or Generic short/long write command
 * @param  ChannelNbr Virtual channel ID
 * @param  Reg Register to be written
 * @param  pData pointer to a buffer of data to be write
 * @param  Size To precise command to be used (short or long)
 * @retval BSP status
 */
static int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
	int32_t ret = BSP_ERROR_NONE;

	if(Size <= 1U)
	{
		if(HAL_DSI_ShortWrite(&hdsi, ChannelNbr, DSI_DCS_SHORT_PKT_WRITE_P1, Reg, (uint32_t)pData[Size]) != HAL_OK)
		{
			ret = BSP_ERROR_BUS_FAILURE;
		}
	}
	else
	{
		if(HAL_DSI_LongWrite(&hdsi, ChannelNbr, DSI_DCS_LONG_PKT_WRITE, Size, (uint32_t)Reg, pData) != HAL_OK)
		{
			ret = BSP_ERROR_BUS_FAILURE;
		}
	}

	return ret;
}

/**
 * @brief  DCS or Generic read command
 * @param  ChannelNbr Virtual channel ID
 * @param  Reg Register to be read
 * @param  pData pointer to a buffer to store the payload of a read back operation.
 * @param  Size  Data size to be read (in byte).
 * @retval BSP status
 */
static int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
	int32_t ret = BSP_ERROR_NONE;

	if(HAL_DSI_Read(&hdsi, ChannelNbr, pData, Size, DSI_DCS_SHORT_PKT_READ, Reg, pData) != HAL_OK)
	{
		ret = BSP_ERROR_BUS_FAILURE;
	}

	return ret;
}

#if (USE_LCD_CTRL_OTM8009A > 0)
/**
 * @brief  Register Bus IOs if component ID is OK
 * @retval error status
 */
static int32_t OTM8009A_Probe(uint32_t ColorCoding, uint32_t Orientation)
{
	int32_t ret;
	uint32_t id;
	OTM8009A_IO_t              IOCtx;
	static OTM8009A_Object_t   OTM8009AObj;

	/* Configure the audio driver */
	IOCtx.Address     = 0;
	IOCtx.GetTick     = BSP_GetTick;
	IOCtx.WriteReg    = DSI_IO_Write;
	IOCtx.ReadReg     = DSI_IO_Read;

	if(OTM8009A_RegisterBusIO(&OTM8009AObj, &IOCtx) != OTM8009A_OK)
	{
		ret = BSP_ERROR_BUS_FAILURE;
	}
	else
	{
		Lcd_CompObj = &OTM8009AObj;

		if(OTM8009A_ReadID(Lcd_CompObj, &id) != OTM8009A_OK)
		{
			ret = BSP_ERROR_COMPONENT_FAILURE;
		}

		else
		{
			Lcd_Drv = (LCD_Drv_t *)(void *) &OTM8009A_LCD_Driver;
			if(Lcd_Drv->Init(Lcd_CompObj, ColorCoding, Orientation) != OTM8009A_OK)
			{
				ret = BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				ret = BSP_ERROR_NONE;
			}
		}
	}
	return ret;
}
#endif /* USE_LCD_CTRL_OTM8009A */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
