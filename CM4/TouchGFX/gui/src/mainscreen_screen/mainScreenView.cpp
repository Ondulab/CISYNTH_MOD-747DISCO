#include <gui/mainscreen_screen/mainScreenView.hpp>

#ifndef SIMULATOR
#ifdef __cplusplus
extern "C" {
#endif

//#include "FreeRTOS.h"
//#include "task.h"
#include "shared.h"
#include "arm_math.h"
#include "quadspi.h"
#include "gui_var.h"
#include "synth.h"
#include "wave_generation.h"
#endif

mainScreenView::mainScreenView()
				{
#ifndef SIMULATOR
	attackSlider.setValue(guiValues.attackSlider);
	releasaSlider.setValue(guiValues.releaseSlider);
#endif
				}

void mainScreenView::setupScreen()
{
	mainScreenViewBase::setupScreen();
}

void mainScreenView::tearDownScreen()
{
	mainScreenViewBase::tearDownScreen();
}

void mainScreenView::attackSliderChanged(int value)
{
#ifndef SIMULATOR
	params.ifft_attack = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
	guiValues.attackSlider = value;
#endif
}

void mainScreenView::releaseSliderChanged(int value)
{
#ifndef SIMULATOR
	params.ifft_release = (int32_t)pow((((float64_t)(100 - value))/100.00)*(log10(20000.00)-log10(1.00))+log10(1.00), 10);
	guiValues.releaseSlider = value;
#endif
}

void mainScreenView::saveButtonClicked()
{
#ifndef SIMULATOR
	QSPI_UpdateData();
#endif
}

void mainScreenView::sawButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SAW_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void mainScreenView::sinButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SIN_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void mainScreenView::sqrButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SQR_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void mainScreenView::waveFormOrderSliderChanged(int value)
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformOrder = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void mainScreenView::startFreqSliderChanged(int value)
{
#ifndef SIMULATOR
	wavesGeneratorParams.startFrequency = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void mainScreenView::commaSliderChanged(int value)
{
#ifndef SIMULATOR
	wavesGeneratorParams.commaPerSemitone = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

#ifndef SIMULATOR
#ifdef __cplusplus
}
#endif
#endif
