#ifndef IFFTSCREENVIEW_HPP
#define IFFTSCREENVIEW_HPP

#include <gui_generated/ifftscreen_screen/ifftScreenViewBase.hpp>
#include <gui/ifftscreen_screen/ifftScreenPresenter.hpp>

class ifftScreenView : public ifftScreenViewBase
{
public:
	ifftScreenView();
    virtual ~ifftScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void attackSliderChanged(int value);
    virtual void releaseSliderChanged(int value);
    virtual void saveButtonClicked();
    virtual void sawButtonSelected();
    virtual void sinButtonSelected();
    virtual void sqrButtonSelected();
    virtual void waveFormOrderSliderChanged(int value);
    virtual void startFreqSliderChanged(int value);
    virtual void commaSliderChanged(int value);
protected:
};

#endif // IFFTSCREENVIEW_HPP
