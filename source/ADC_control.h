#ifndef __ADC_CONTROL__
#define __ADC_CONTROL__

#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "fsl_adc16.h"
#include "math.h"
#include "circular_buffer.h"
#include "DMA_control.h"
#include "DAC_control.h"
#include "semphr.h"

#define ADC16_BASE ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL 0U /*PTE20, ADC0_SE0 */

extern circularBuffer cBuffer;
extern uint16_t data[MAX_SINE_WAVE_VALUES];
extern uint16_t dspBuffer[MAX_SINE_WAVE_VALUES];
extern uint8_t adcSineWaveCount;
extern TimerHandle_t ADC_Timer;

void vADC_CallBack(TimerHandle_t xTimer);
void initADC_Timer();
void initADC0();
void processDSP_BufferAndOutputReport(uint16_t* buffer);

#endif
