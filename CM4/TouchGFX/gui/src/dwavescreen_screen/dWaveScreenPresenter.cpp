#include <gui/dwavescreen_screen/dWaveScreenView.hpp>
#include <gui/dwavescreen_screen/dWaveScreenPresenter.hpp>

#ifndef SIMULATOR
#include "shared.h"
#include "audio.h"
#endif

dWaveScreenPresenter::dWaveScreenPresenter(dWaveScreenView& v)
    : view(v)
{

}

void dWaveScreenPresenter::activate()
{
#ifndef SIMULATOR
	audio_UnMute();
	shared_var.mode = DWAVE_MODE;
#endif
}

void dWaveScreenPresenter::deactivate()
{
#ifndef SIMULATOR
	audio_Mute();
	shared_var.mode = MENU_MODE;
#endif
}
