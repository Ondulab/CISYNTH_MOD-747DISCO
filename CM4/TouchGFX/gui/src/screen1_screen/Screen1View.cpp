#include <gui/screen1_screen/Screen1View.hpp>
#include "shared.h"
#include "arm_math.h"

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::Attack_Slider_Callback(int value)
{
	params.ifft_attack = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
}

void Screen1View::Release_Slider_Callback(int value)
{
	params.ifft_release = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
}
