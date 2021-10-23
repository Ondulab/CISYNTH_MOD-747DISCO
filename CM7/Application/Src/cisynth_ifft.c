/*
 * cisynth_eth.c
 *
 *  Created on: May 31, 2020
 *      Author: zhonx
 */

#include "main.h"

#include "cisynth_ifft.h"
#include "synth.h"
#include "config.h"
#include "pcm5102.h"

#include "lwip.h"

#include "stdio.h"
#include "stdbool.h"

extern __IO uint32_t synth_process_cnt;

/**
 * @brief  The application entry point.
 * @retval int
 */
#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")
int cisynth_ifft(void)
{
	printf("------ BW IFFT MODE START -----\n");
	printf("-------------------------------\n");

	synth_IfftInit();

	while (1)
	{
		MX_LWIP_Process();
		synth_AudioProcess(IFFT_MODE);
	}
}
#pragma GCC pop_options
