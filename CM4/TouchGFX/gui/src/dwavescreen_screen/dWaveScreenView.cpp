#include <gui/dwavescreen_screen/dWaveScreenView.hpp>

#include "shared.h"
#include "arm_math.h"
#include "quadspi.h"
#include "gui_var.h"
#include "synth.h"

dWaveScreenView::dWaveScreenView()
{
	shared_var.directRead_Mode = NORMAL_READ;
}

void dWaveScreenView::setupScreen()
{
    dWaveScreenViewBase::setupScreen();
}

void dWaveScreenView::tearDownScreen()
{
    dWaveScreenViewBase::tearDownScreen();
//    for (int16_t i = 0; i < CIS_PIXELS_NB; i++)
//    {
//    	dynamicGraph1.DynamicDataGraph(i, imageData[i]);
//    }
}

void dWaveScreenView::oct_0()
{

}

void dWaveScreenView::oct_1()
{

}

void dWaveScreenView::oct_2()
{

}

void dWaveScreenView::oct_3()
{

}

void dWaveScreenView::oct_4()
{

}

void dWaveScreenView::slider_Blur_Updated(int value)
{

}

void dWaveScreenView::slider_CV_Updated(int value)
{

}

void dWaveScreenView::note_Ad()
{

}

void dWaveScreenView::note_Gd()
{

}

void dWaveScreenView::note_Fd()
{

}

void dWaveScreenView::note_Dd()
{

}

void dWaveScreenView::note_Cd()
{

}

void dWaveScreenView::note_A()
{

}

void dWaveScreenView::note_B()
{

}

void dWaveScreenView::note_C()
{

}

void dWaveScreenView::note_D()
{

}

void dWaveScreenView::note_E()
{

}

void dWaveScreenView::note_F()
{

}

void dWaveScreenView::note_G()
{

}

void dWaveScreenView::toggle_Button_CV()
{
	shared_var.CV_or_Keyboard = CV_ON;
}

void dWaveScreenView::toggle_Button_Blur()
{

}

void dWaveScreenView::normaRead()
{
	shared_var.directRead_Mode = NORMAL_READ;
}

void dWaveScreenView::normalReverseRead()
{
	shared_var.directRead_Mode = NORMAL_REVERSE_READ;
}

void dWaveScreenView::dualRead()
{
	shared_var.directRead_Mode = DUAL_READ;
}
