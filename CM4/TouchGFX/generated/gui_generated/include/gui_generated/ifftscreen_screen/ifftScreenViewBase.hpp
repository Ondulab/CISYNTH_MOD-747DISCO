/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef IFFTSCREENVIEWBASE_HPP
#define IFFTSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/ifftscreen_screen/ifftScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/graph/GraphScroll.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>

class ifftScreenViewBase : public touchgfx::View<ifftScreenPresenter>
{
public:
    ifftScreenViewBase();
    virtual ~ifftScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void attackSliderChanged(int value)
    {
        // Override and implement this function in ifftScreen
    }

    virtual void releaseSliderChanged(int value)
    {
        // Override and implement this function in ifftScreen
    }

    virtual void saveButtonClicked()
    {
        // Override and implement this function in ifftScreen
    }

    virtual void sawButtonSelected()
    {
        // Override and implement this function in ifftScreen
    }

    virtual void sqrButtonSelected()
    {
        // Override and implement this function in ifftScreen
    }

    virtual void sinButtonSelected()
    {
        // Override and implement this function in ifftScreen
    }

    virtual void waveFormOrderSliderChanged(int value)
    {
        // Override and implement this function in ifftScreen
    }

    virtual void startFreqSliderChanged(int value)
    {
        // Override and implement this function in ifftScreen
    }

    virtual void commaSliderChanged(int value)
    {
        // Override and implement this function in ifftScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Slider slider1;
    touchgfx::BoxWithBorder boxWithBorder1;
    touchgfx::Slider attackSlider;
    touchgfx::Slider releasaSlider;
    touchgfx::GraphScroll<100> dynamicGraph1_1;
    touchgfx::GraphElementLine dynamicGraph1_1Line1;
    touchgfx::PainterRGB888 dynamicGraph1_1Line1Painter;
    touchgfx::RadioButton SIN_Button;
    touchgfx::RadioButton SQR_Button;
    touchgfx::RadioButton SAW_Button;
    touchgfx::Slider waveFormOrderSlider;
    touchgfx::Slider commaSlider;
    touchgfx::TextArea textHarmonization;
    touchgfx::TextArea textAttack;
    touchgfx::TextArea textRelease;
    touchgfx::TextArea textSAW;
    touchgfx::TextArea textSIN;
    touchgfx::TextArea textSQR;
    touchgfx::TextArea textComma;
    touchgfx::Slider startFreqSlider;
    touchgfx::TextArea textStartFreq;
    touchgfx::ButtonWithLabel saveButton;
    touchgfx::TextArea textOrder;
    touchgfx::ButtonWithLabel menuButton;
    touchgfx::RadioButtonGroup<3> radioButtonGroup1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<ifftScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<ifftScreenViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;
    touchgfx::Callback<ifftScreenViewBase, const touchgfx::Slider&, int> sliderValueConfirmedCallback;
    touchgfx::Callback<ifftScreenViewBase, const touchgfx::AbstractButton&> radioButtonSelectedCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);
    void sliderValueConfirmedCallbackHandler(const touchgfx::Slider& src, int value);
    void radioButtonSelectedCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // IFFTSCREENVIEWBASE_HPP
