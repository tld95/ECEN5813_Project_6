#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "fsl_dac.h"
#include "math.h"

#define MAX_SINE_WAVE_VALUES 100

// Referenced dac_basic.c NXP example project
#define DAC_BASEADDR DAC0
#define MAX_DAC_OUTPUT 4095
#define DAC_VREF 3.3

void vDAC_CallBack(TimerHandle_t xTimer);
void initDAC_Timer();
void initDAC0();
