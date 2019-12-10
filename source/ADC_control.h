/*
 *  PES Project Six ADC Control header code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
 *	https://www.freertos.org
 *	SDK_2.x_FRDM-KL25Z
 */

#ifndef __ADC_CONTROL_H__
#define __ADC_CONTROL_H__

#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "fsl_adc16.h"
#include "math.h"
#include "DMA_control.h"
#include "DAC_control.h"
#include "semphr.h"

#define ADC16_BASE ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL 0U /*PTE20, ADC0_SE0 */

extern uint16_t data[MAX_SINE_WAVE_VALUES];
extern uint16_t dspBuffer[MAX_SINE_WAVE_VALUES];
extern uint8_t adcSineWaveCount;
extern TimerHandle_t ADC_Timer;

// ADC timer call back
void vADC_CallBack(TimerHandle_t xTimer);
// ADC timer initialization
void initADC_Timer();
// ADC initialization
void initADC0();

#endif
