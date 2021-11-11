#ifndef MAINSCREENVIEW_HPP
#define MAINSCREENVIEW_HPP

#include <gui_generated/mainscreen_screen/mainScreenViewBase.hpp>
#include <gui/mainscreen_screen/mainScreenPresenter.hpp>

class mainScreenView : public mainScreenViewBase
{
public:
    mainScreenView();
    virtual ~mainScreenView() {}
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

#endif // MAINSCREENVIEW_HPP
