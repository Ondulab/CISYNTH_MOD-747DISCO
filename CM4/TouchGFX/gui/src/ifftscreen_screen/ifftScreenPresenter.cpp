#include <gui/ifftscreen_screen/ifftScreenView.hpp>
#include <gui/ifftscreen_screen/ifftScreenPresenter.hpp>

#ifndef SIMULATOR
#include "shared.h"
#include "audio.h"
#endif

ifftScreenPresenter::ifftScreenPresenter(ifftScreenView& v)
    : view(v)
{

}

void ifftScreenPresenter::activate()
{
#ifndef SIMULATOR
	audio_UnMute();
	shared_var.mode = IFFT_MODE;
#endif
}

void ifftScreenPresenter::deactivate()
{
#ifndef SIMULATOR
	audio_Mute();
	shared_var.mode = MENU_MODE;
#endif
}
