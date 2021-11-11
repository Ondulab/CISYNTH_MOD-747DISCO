#include <gui/screen1_screen/Screen1View.hpp>

#ifndef SIMULATOR
#include "shared.h"
#include "arm_math.h"
#include "quadspi.h"
#include "gui_var.h"
#endif

Screen1View::Screen1View()
{
#ifndef SIMULATOR
	attackSlider.setValue(guiValues.attackSlider);
	releasaSlider.setValue(guiValues.releaseSlider);
#endif
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::attackSliderChanged(int value)
{
#ifndef SIMULATOR
	params.ifft_attack = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
	guiValues.attackSlider = value;
#endif
}

void Screen1View::releaseSliderChanged(int value)
{
#ifndef SIMULATOR
	params.ifft_release = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
	guiValues.releaseSlider = value;
#endif
}

void Screen1View::saveButtonClicked()
{
#ifndef SIMULATOR
	QSPI_UpdateData();
#endif
}
