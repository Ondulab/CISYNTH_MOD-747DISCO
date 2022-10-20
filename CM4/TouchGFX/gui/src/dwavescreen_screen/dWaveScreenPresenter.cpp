#include <gui/dwavescreen_screen/dWaveScreenView.hpp>
#include <gui/dwavescreen_screen/dWaveScreenPresenter.hpp>
#include "shared.h"
#include "audio.h"

dWaveScreenPresenter::dWaveScreenPresenter(dWaveScreenView& v)
    : view(v)
{

}

void dWaveScreenPresenter::activate()
{
	audio_UnMute();
	shared_var.mode = DWAVE_MODE;
}

void dWaveScreenPresenter::deactivate()
{
	audio_Mute();
	shared_var.mode = MENU_MODE;
}
