#include <gui/ifftscreen_screen/ifftScreenView.hpp>
#include <gui/ifftscreen_screen/ifftScreenPresenter.hpp>
#include "shared.h"
#include "pcm5102.h"

ifftScreenPresenter::ifftScreenPresenter(ifftScreenView& v)
    : view(v)
{

}

void ifftScreenPresenter::activate()
{
	pcm5102_UnMute();
	shared_var.mode = IFFT_MODE;
}

void ifftScreenPresenter::deactivate()
{
	pcm5102_Mute();
	shared_var.mode = MENU_MODE;
}
