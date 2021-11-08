/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1VIEWBASE_HPP
#define SCREEN1VIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/graph/GraphWrapAndClear.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/widgets/canvas/PainterRGB888.hpp>
#include <touchgfx/widgets/RadioButton.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/RadioButtonGroup.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void Attack_Slider_Callback(int value)
    {
        // Override and implement this function in Screen1
    }

    virtual void Release_Slider_Callback(int value)
    {
        // Override and implement this function in Screen1
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
    touchgfx::Slider slider2;
    touchgfx::Slider slider3;
    touchgfx::GraphWrapAndClear<100> dynamicGraph1_1;
    touchgfx::GraphElementLine dynamicGraph1_1Line1;
    touchgfx::PainterRGB888 dynamicGraph1_1Line1Painter;
    touchgfx::RadioButton radioButton1;
    touchgfx::RadioButton radioButton2;
    touchgfx::RadioButton radioButton3;
    touchgfx::Slider slider6;
    touchgfx::Slider slider8;
    touchgfx::TextArea textArea1;
    touchgfx::TextArea textArea1_1;
    touchgfx::TextArea textArea1_1_1;
    touchgfx::TextArea textArea1_1_1_1_1;
    touchgfx::TextArea textArea1_1_1_1_1_1;
    touchgfx::TextArea textArea1_1_1_1_1_1_1;
    touchgfx::TextArea textArea1_1_1_1_1_2;
    touchgfx::Slider slider8_1;
    touchgfx::TextArea textArea1_1_1_1_1_2_1;
    touchgfx::RadioButtonGroup<3> radioButtonGroup1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<Screen1ViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;

    /*
     * Callback Handler Declarations
     */
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREEN1VIEWBASE_HPP
