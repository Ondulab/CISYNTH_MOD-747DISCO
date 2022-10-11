#ifndef DWAVESCREENVIEW_HPP
#define DWAVESCREENVIEW_HPP

#include <gui_generated/dwavescreen_screen/dWaveScreenViewBase.hpp>
#include <gui/dwavescreen_screen/dWaveScreenPresenter.hpp>

class dWaveScreenView : public dWaveScreenViewBase
{
public:
    dWaveScreenView();
    virtual ~dWaveScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DWAVESCREENVIEW_HPP
