#include <gui/ifftscreen_screen/ifftScreenView.hpp>
#include <gui/ifftscreen_screen/ifftScreenPresenter.hpp>
#include "shared.h"
#include "audio.h"

ifftScreenPresenter::ifftScreenPresenter(ifftScreenView& v)
    : view(v)
{

}

void ifftScreenPresenter::activate()
{
	audio_UnMute();
	shared_var.mode = IFFT_MODE;
}

void ifftScreenPresenter::deactivate()
{
	audio_Mute();
	shared_var.mode = MENU_MODE;
}
