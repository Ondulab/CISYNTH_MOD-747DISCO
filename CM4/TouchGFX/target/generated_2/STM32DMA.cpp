/**
  ******************************************************************************
  * File Name          : STM32DMA.cpp
  ******************************************************************************
  * This file is generated by TouchGFX Generator 4.18.0. Please, do not edit!
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include <STM32DMA.hpp>
#include <assert.h>

STM32DMA::STM32DMA()
    : DMA_Interface(q), q(&b, 1)
{
}

touchgfx::BlitOperations STM32DMA::getBlitCaps()
{
    return static_cast<touchgfx::BlitOperations>(0);
}

void STM32DMA::setupDataCopy(const touchgfx::BlitOp& blitOp)
{
    assert(0 && "DMA operation not supported");
}

void STM32DMA::setupDataFill(const touchgfx::BlitOp& blitOp)
{
    assert(0 && "DMA operation not supported");
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
