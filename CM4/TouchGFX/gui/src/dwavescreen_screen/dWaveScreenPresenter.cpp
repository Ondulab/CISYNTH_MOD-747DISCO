#include <gui/dwavescreen_screen/dWaveScreenView.hpp>
#include <gui/dwavescreen_screen/dWaveScreenPresenter.hpp>
#include "shared.h"
#include "pcm5102.h"

dWaveScreenPresenter::dWaveScreenPresenter(dWaveScreenView& v)
    : view(v)
{

}

void dWaveScreenPresenter::activate()
{
	pcm5102_UnMute();
	shared_var.mode = DWAVE_MODE;
}

void dWaveScreenPresenter::deactivate()
{
	pcm5102_Mute();
	shared_var.mode = MENU_MODE;
}
