/*
 * Copyright 2016-2019 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/*
 *  PES Project Six main source code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
 *	https://www.freertos.org
 *	SDK_2.x_FRDM-KL25Z
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "timing_control.h"
#include "DAC_control.h"
#include "ADC_control.h"
#include "DMA_control.h"
#include "DSP_control.h"

#define LED3_PORT GPIOD
#define LED3_PIN 1U

TimerHandle_t Program_Timer;

// Call back function for stopping ADC/DAC FREERTOS timers after max runs of program are completed
// Referenced https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void vProgram_CallBack(TimerHandle_t xTimer)
{
	if (dacSineWaveCount >= MAX_RUNS)
	{
		xTimerStop(DAC_Timer, 0);
	}
	if (adcSineWaveCount >= MAX_RUNS)
	{
		xTimerStop(ADC_Timer, 0);
	}
}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    LED_BLUE_INIT(1);

    initDAC0();
#ifdef PROGRAM_TWO
    initADC0();
    initDMA0();
#endif

    Log_enable();
    // Runs at 1KHz
    initLoggerTimer();
    // Runs at 10Hz
    initDAC_Timer();
#ifdef PROGRAM_TWO
    initADC_Timer();
#endif

#ifndef PROGRAM_TWO
    Log_string(STATUS_LEVEL, MAIN, "Program 1 Started");
#else
    Log_string(STATUS_LEVEL, MAIN, "Program 2 Started");
#endif

    // Starts FREERTOS timer to check for Project 6 Program completion
    // Referenced https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
	Program_Timer = xTimerCreate("Program Complete", pdMS_TO_TICKS(100), pdTRUE, (void *) 0, vProgram_CallBack);
    if (Program_Timer == NULL)
    {

    }
    else
    {
    	if (xTimerStart(Program_Timer, 0) != pdPASS)
    	{

    	}
    }

    // Start FREERTOS scheduler
    vTaskStartScheduler();
    while (1)
    {
    	__asm("NOP");
    }

    return 0 ;
}
