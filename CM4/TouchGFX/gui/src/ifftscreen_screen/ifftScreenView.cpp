#include <gui/ifftscreen_screen/ifftScreenView.hpp>

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

#ifndef HSEM_ID_1
#define HSEM_ID_1 (0U) /* HW semaphore 0*/
#endif

#endif

ifftScreenView::ifftScreenView()
{
#ifndef SIMULATOR
	attackSlider.setValue(guiValues.attackSlider);
	releasaSlider.setValue(guiValues.releaseSlider);
	commaSlider.setValue(guiValues.commaPerSemitoneSlider);
	startFreqSlider.setValue(guiValues.startFreqSlider);
#endif
}

void ifftScreenView::setupScreen()
{
	ifftScreenViewBase::setupScreen();
}

void ifftScreenView::tearDownScreen()
{
	ifftScreenViewBase::tearDownScreen();
}

void ifftScreenView::attackSliderChanged(int value)
{
#ifndef SIMULATOR
	//sanity check
	if (value == 0)
		value = 1;
	if (value > 100)
		value = 100;
	for (int32_t note = 0; note < NUMBER_OF_NOTES; note++)
	{
		waves[note].volume_increment = 1.00/(float32_t)value * waves[note].max_volume_increment;
	}
	guiValues.attackSlider = value;
#endif
}

void ifftScreenView::releaseSliderChanged(int value)
{
#ifndef SIMULATOR
	//sanity check
	if (value == 0)
		value = 1;
	if (value > 100)
		value = 100;
	for (int32_t note = 0; note < NUMBER_OF_NOTES; note++)
	{
		waves[note].volume_decrement = 1.00/(float32_t)value * waves[note].max_volume_decrement;
	}
	guiValues.releaseSlider = value;
#endif
}

void ifftScreenView::saveButtonClicked()
{
#ifndef SIMULATOR
	QSPI_UpdateData();
#endif
}

void ifftScreenView::sawButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SAW_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void ifftScreenView::sinButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SIN_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void ifftScreenView::sqrButtonSelected()
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformType = SQR_WAVE;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void ifftScreenView::waveFormOrderSliderChanged(int value)
{
#ifndef SIMULATOR
	wavesGeneratorParams.waveformOrder = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
#endif
}

void ifftScreenView::startFreqSliderChanged(int value)
{
#ifndef SIMULATOR
	//sanity check
	if (value < 20)
		value = 20;
	if (value > 10000)
		value = 10000;
	/* CM4 takes HW sempahore 0 to inform CM7 that he finished his job */
	HAL_HSEM_FastTake(HSEM_ID_1);
	wavesGeneratorParams.startFrequency = value;
	params.start_frequency = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
	/* Do not forget to release the HW semaphore 0 once needed */
	HAL_HSEM_Release(HSEM_ID_1, 0);
	guiValues.startFreqSlider = value;
#endif
}

void ifftScreenView::commaSliderChanged(int value)
{
#ifndef SIMULATOR
	//sanity check
	if (value < 2)
		value = 2;
	if (value > 8)
		value = 8;
	/* CM4 takes HW sempahore 0 to inform CM7 that he finished his job */
	HAL_HSEM_FastTake(HSEM_ID_1);
	wavesGeneratorParams.commaPerSemitone = value;
	params.comma_per_semitone = value;
	init_waves(unitary_waveform, waves, &wavesGeneratorParams);
	/* Do not forget to release the HW semaphore 0 once needed */
	HAL_HSEM_Release(HSEM_ID_1, 0);
	guiValues.commaPerSemitoneSlider = value;
#endif
}

#ifndef SIMULATOR
#ifdef __cplusplus
}
#endif
#endif
