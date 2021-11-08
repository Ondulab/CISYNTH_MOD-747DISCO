/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>


Screen1ViewBase::Screen1ViewBase() :
    sliderValueChangedCallback(this, &Screen1ViewBase::sliderValueChangedCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    box1.setPosition(0, 0, 800, 480);
    box1.setColor(touchgfx::Color::getColorFromRGB(56, 44, 44));

    slider1.setXY(15, 255);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider1.setupHorizontalSlider(5, 24, 0, 0, 615);
    slider1.setValueRange(0, 100);
    slider1.setValue(90);

    boxWithBorder1.setPosition(15, 38, 237, 193);
    boxWithBorder1.setColor(touchgfx::Color::getColorFromRGB(64, 64, 64));
    boxWithBorder1.setBorderColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    boxWithBorder1.setBorderSize(5);

    slider2.setXY(15, 344);
    slider2.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider2.setupHorizontalSlider(5, 24, 0, 0, 615);
    slider2.setValueRange(0, 100);
    slider2.setValue(75);
    slider2.setNewValueCallback(sliderValueChangedCallback);

    slider3.setXY(15, 412);
    slider3.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_SLIDER_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_HORIZONTAL_LARGE_INDICATORS_SLIDER_ROUND_NOB_ID));
    slider3.setupHorizontalSlider(5, 24, 0, 0, 615);
    slider3.setValueRange(0, 100);
    slider3.setValue(25);
    slider3.setNewValueCallback(sliderValueChangedCallback);

    dynamicGraph1_1.setScale(1);
    dynamicGraph1_1.setPosition(21, 45, 224, 178);
    dynamicGraph1_1.setGraphAreaMargin(0, 0, 0, 0);
    dynamicGraph1_1.setGraphAreaPadding(0, 0, 0, 0);
    dynamicGraph1_1.setGraphRangeY(0, 100);

    dynamicGraph1_1Line1.setScale(1);
    dynamicGraph1_1Line1Painter.setColor(touchgfx::Color::getColorFromRGB(157, 240, 137));
    dynamicGraph1_1Line1.setPainter(dynamicGraph1_1Line1Painter);
    dynamicGraph1_1Line1.setLineWidth(2);
    dynamicGraph1_1.addGraphElement(dynamicGraph1_1Line1);

    dynamicGraph1_1.addDataPoint(76.91513075821447f);
    dynamicGraph1_1.addDataPoint(74.95847205738002f);
    dynamicGraph1_1.addDataPoint(66.88264223087391f);
    dynamicGraph1_1.addDataPoint(53.647033296479556f);
    dynamicGraph1_1.addDataPoint(37.515248726427586f);
    dynamicGraph1_1.addDataPoint(21.539840229577827f);
    dynamicGraph1_1.addDataPoint(8.850699244916715f);
    dynamicGraph1_1.addDataPoint(1.9199073787026961f);
    dynamicGraph1_1.addDataPoint(1.9817815367134486f);
    dynamicGraph1_1.addDataPoint(8.74911546472832f);
    dynamicGraph1_1.addDataPoint(20.49434288465553f);
    dynamicGraph1_1.addDataPoint(34.4753246565754f);
    dynamicGraph1_1.addDataPoint(47.60139571075864f);
    dynamicGraph1_1.addDataPoint(57.17681988473984f);
    dynamicGraph1_1.addDataPoint(61.54014821341059f);
    dynamicGraph1_1.addDataPoint(60.44377291035259f);
    dynamicGraph1_1.addDataPoint(55.081833661579054f);
    dynamicGraph1_1.addDataPoint(47.76094002988795f);
    dynamicGraph1_1.addDataPoint(41.295820468270435f);
    dynamicGraph1_1.addDataPoint(38.27941667907413f);
    dynamicGraph1_1.addDataPoint(40.407774759260434f);
    dynamicGraph1_1.addDataPoint(48.02662143085193f);
    dynamicGraph1_1.addDataPoint(60.01215673235865f);
    dynamicGraph1_1.addDataPoint(74.01664173437749f);
    dynamicGraph1_1.addDataPoint(87.0198112998448f);
    dynamicGraph1_1.addDataPoint(96.0520550524034f);
    dynamicGraph1_1.addDataPoint(98.91294887774505f);
    dynamicGraph1_1.addDataPoint(94.7095588891703f);
    dynamicGraph1_1.addDataPoint(84.0827351084942f);
    dynamicGraph1_1.addDataPoint(69.06568957476082f);
    dynamicGraph1_1.addDataPoint(52.60886347964956f);
    dynamicGraph1_1.addDataPoint(37.88650833531777f);
    dynamicGraph1_1.addDataPoint(27.553608055636797f);
    dynamicGraph1_1.addDataPoint(23.133694755065278f);
    dynamicGraph1_1.addDataPoint(24.685958909670642f);
    dynamicGraph1_1.addDataPoint(30.831538263993757f);
    dynamicGraph1_1.addDataPoint(39.13092983056609f);
    dynamicGraph1_1.addDataPoint(46.71853923481417f);
    dynamicGraph1_1.addDataPoint(51.03750505272389f);
    dynamicGraph1_1.addDataPoint(50.49358525032922f);
    dynamicGraph1_1.addDataPoint(44.8668828017244f);
    dynamicGraph1_1.addDataPoint(35.37976005734174f);
    dynamicGraph1_1.addDataPoint(24.40375063570744f);
    dynamicGraph1_1.addDataPoint(14.87698196124432f);
    dynamicGraph1_1.addDataPoint(9.574819893802452f);
    dynamicGraph1_1.addDataPoint(10.412706042902489f);
    dynamicGraph1_1.addDataPoint(17.95258291867563f);
    dynamicGraph1_1.addDataPoint(31.234724548499887f);
    dynamicGraph1_1.addDataPoint(47.97738401004891f);
    dynamicGraph1_1.addDataPoint(65.09676177096509f);
    dynamicGraph1_1.addDataPoint(79.42154828814611f);
    dynamicGraph1_1.addDataPoint(88.42870382691223f);
    dynamicGraph1_1.addDataPoint(90.82194610368326f);
    dynamicGraph1_1.addDataPoint(86.81289435645218f);
    dynamicGraph1_1.addDataPoint(78.03745597644537f);
    dynamicGraph1_1.addDataPoint(67.12921377565404f);
    dynamicGraph1_1.addDataPoint(57.05529566767876f);
    dynamicGraph1_1.addDataPoint(50.37810108873973f);
    dynamicGraph1_1.addDataPoint(48.62411167450502f);
    dynamicGraph1_1.addDataPoint(51.914473249497476f);
    dynamicGraph1_1.addDataPoint(58.947626017279255f);
    dynamicGraph1_1.addDataPoint(67.33774307160061f);
    dynamicGraph1_1.addDataPoint(74.22533480710419f);
    dynamicGraph1_1.addDataPoint(77.00944989216141f);
    dynamicGraph1_1.addDataPoint(74.02094644154118f);
    dynamicGraph1_1.addDataPoint(64.97052332952171f);
    dynamicGraph1_1.addDataPoint(51.060253528368214f);
    dynamicGraph1_1.addDataPoint(34.7296963465068f);
    dynamicGraph1_1.addDataPoint(19.097118252937953f);
    dynamicGraph1_1.addDataPoint(7.231121590641596f);
    dynamicGraph1_1.addDataPoint(1.4295931300309483f);
    dynamicGraph1_1.addDataPoint(2.681313095390248f);
    dynamicGraph1_1.addDataPoint(10.44107630059965f);
    dynamicGraph1_1.addDataPoint(22.772693315527256f);
    dynamicGraph1_1.addDataPoint(36.824487031666486f);
    dynamicGraph1_1.addDataPoint(49.520803179449544f);
    dynamicGraph1_1.addDataPoint(58.30049886361974f);
    dynamicGraph1_1.addDataPoint(61.72217418731098f);
    dynamicGraph1_1.addDataPoint(59.78885014100121f);
    dynamicGraph1_1.addDataPoint(53.913706592395116f);
    dynamicGraph1_1.addDataPoint(46.53661924754473f);
    dynamicGraph1_1.addDataPoint(40.48687033577089f);
    dynamicGraph1_1.addDataPoint(38.24964791173815f);
    dynamicGraph1_1.addDataPoint(41.31756691466487f);
    dynamicGraph1_1.addDataPoint(49.7875506846562f);
    dynamicGraph1_1.addDataPoint(62.303292883543634f);
    dynamicGraph1_1.addDataPoint(76.35872688813004f);
    dynamicGraph1_1.addDataPoint(88.88934188476605f);
    dynamicGraph1_1.addDataPoint(97.00746518644057f);
    dynamicGraph1_1.addDataPoint(98.70207657267358f);
    dynamicGraph1_1.addDataPoint(93.33211056213656f);
    dynamicGraph1_1.addDataPoint(81.79242711882475f);
    dynamicGraph1_1.addDataPoint(66.31146207030366f);
    dynamicGraph1_1.addDataPoint(49.92941929607714f);
    dynamicGraph1_1.addDataPoint(35.78382899391637f);
    dynamicGraph1_1.addDataPoint(26.376188429112016f);
    dynamicGraph1_1.addDataPoint(22.997852073102976f);
    dynamicGraph1_1.addDataPoint(25.45421234594788f);
    dynamicGraph1_1.addDataPoint(32.15307181027244f);
    dynamicGraph1_1.addDataPoint(40.533974063799064f);

    radioButton1.setXY(271, 112);
    radioButton1.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButton1.setSelected(false);
    radioButton1.setDeselectionEnabled(true);

    radioButton2.setXY(271, 187);
    radioButton2.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButton2.setSelected(false);
    radioButton2.setDeselectionEnabled(false);

    radioButton3.setXY(271, 38);
    radioButton3.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_INACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_PRESSED_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_ACTIVE_ID), touchgfx::Bitmap(BITMAP_DARK_CHECK_BUTTONS_CHECK_MARK_NORMAL_ID));
    radioButton3.setSelected(true);
    radioButton3.setDeselectionEnabled(false);

    slider6.setXY(378, 38);
    slider6.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_INDICATORS_SLIDER3_VERTICAL_ROUND_NOB_ID));
    slider6.setupVerticalSlider(0, 0, 3, 4, 135);
    slider6.setValueRange(0, 100);
    slider6.setValue(0);

    slider8.setXY(530, 38);
    slider8.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_INDICATORS_SLIDER3_VERTICAL_ROUND_NOB_ID));
    slider8.setupVerticalSlider(0, 0, 3, 4, 135);
    slider8.setValueRange(0, 100);
    slider8.setValue(0);

    textArea1.setXY(710, 277);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_9TY6));

    textArea1_1.setXY(710, 366);
    textArea1_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1.setLinespacing(0);
    textArea1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ECYK));

    textArea1_1_1.setXY(710, 434);
    textArea1_1_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1.setLinespacing(0);
    textArea1_1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_ISHT));

    textArea1_1_1_1_1.setXY(324, 48);
    textArea1_1_1_1_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1_1_1.setLinespacing(0);
    textArea1_1_1_1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SYL5));

    textArea1_1_1_1_1_1.setXY(324, 122);
    textArea1_1_1_1_1_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1_1_1_1.setLinespacing(0);
    textArea1_1_1_1_1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_XHCB));

    textArea1_1_1_1_1_1_1.setXY(324, 198);
    textArea1_1_1_1_1_1_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1_1_1_1_1.setLinespacing(0);
    textArea1_1_1_1_1_1_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_XP6B));

    textArea1_1_1_1_1_2.setXY(512, 13);
    textArea1_1_1_1_1_2.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1_1_1_2.setLinespacing(0);
    textArea1_1_1_1_1_2.setTypedText(touchgfx::TypedText(T___SINGLEUSE_M30I));

    slider8_1.setXY(647, 38);
    slider8_1.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_BACK_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_SLIDER3_VERTICAL_ROUND_FILL_ID), touchgfx::Bitmap(BITMAP_DARK_SLIDER_VERTICAL_SMALL_INDICATORS_SLIDER3_VERTICAL_ROUND_NOB_ID));
    slider8_1.setupVerticalSlider(0, 0, 3, 4, 135);
    slider8_1.setValueRange(0, 100);
    slider8_1.setValue(0);

    textArea1_1_1_1_1_2_1.setXY(629, 13);
    textArea1_1_1_1_1_2_1.setColor(touchgfx::Color::getColorFromRGB(176, 176, 176));
    textArea1_1_1_1_1_2_1.setLinespacing(0);
    textArea1_1_1_1_1_2_1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_SKGI));

    add(__background);
    add(box1);
    add(slider1);
    add(boxWithBorder1);
    add(slider2);
    add(slider3);
    add(dynamicGraph1_1);
    add(radioButton1);
    add(radioButton2);
    add(radioButton3);
    add(slider6);
    add(slider8);
    add(textArea1);
    add(textArea1_1);
    add(textArea1_1_1);
    add(textArea1_1_1_1_1);
    add(textArea1_1_1_1_1_1);
    add(textArea1_1_1_1_1_1_1);
    add(textArea1_1_1_1_1_2);
    add(slider8_1);
    add(textArea1_1_1_1_1_2_1);
    radioButtonGroup1.add(radioButton1);
    radioButtonGroup1.add(radioButton2);
    radioButtonGroup1.add(radioButton3);
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value)
{
    if (&src == &slider2)
    {
        //Attack_Slider
        //When slider2 value changed call virtual function
        //Call Attack_Slider_Callback
        Attack_Slider_Callback(value);
    }
    else if (&src == &slider3)
    {
        //Release_Slider
        //When slider3 value changed call virtual function
        //Call Release_Slider_Callback
        Release_Slider_Callback(value);
    }
}
