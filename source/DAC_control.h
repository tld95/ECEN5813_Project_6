#ifndef __DAC_CONTROL__
#define __DAC_CONTROL__

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

void vDAC_CallBack(TimerHandle_t xTimer);
void initDAC_Timer();
void initDAC0();

#endif
