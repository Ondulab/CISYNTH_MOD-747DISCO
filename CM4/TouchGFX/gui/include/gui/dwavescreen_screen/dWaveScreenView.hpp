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
    virtual void oct_1();
    virtual void oct_2();
    virtual void oct_0();
    virtual void oct_3();
    virtual void oct_4();
    virtual void slider_Blur_Updated(int value);
    virtual void slider_CV_Updated(int value);
    virtual void note_Ad();
    virtual void note_Gd();
    virtual void note_Fd();
    virtual void note_Dd();
    virtual void note_Cd();
    virtual void note_A();
    virtual void note_B();
    virtual void note_C();
    virtual void note_D();
    virtual void note_E();
    virtual void note_F();
    virtual void note_G();
    virtual void toggle_Button_CV();
    virtual void toggle_Button_Blur();
    virtual void normaRead();
    virtual void normalReverseRead();
    virtual void dualRead();
protected:
};

#endif // DWAVESCREENVIEW_HPP
