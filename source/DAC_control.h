/*
 *  PES Project Six DAC Control header code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
 *	https://www.freertos.org
 *	SDK_2.x_FRDM-KL25Z
 */

#ifndef __DAC_CONTROL_H__
#define __DAC_CONTROL_H__

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "fsl_dac.h"
#include "semphr.h"
#include "math.h"
#include "board.h"

#define MAX_SINE_WAVE_VALUES 81
#define MAX_RUNS 1

// Referenced dac_basic.c NXP example project
#define DAC_BASEADDR DAC0
#define MAX_DAC_OUTPUT 4095
#define DAC_VREF 3.3

extern SemaphoreHandle_t xSemaphore;
extern uint8_t dacSineWaveCount;
extern TimerHandle_t DAC_Timer;

// DAC Call Back for timer
void vDAC_CallBack(TimerHandle_t xTimer);
// DAC timer initialization
void initDAC_Timer();
// DAC initialization
void initDAC0();

#endif
