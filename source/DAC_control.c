#include "DAC_control.h"
/*
static const float sineWave[MAX_SINE_WAVE_VALUES] = {
	1.0, 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5,
	1.55, 1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2.0,
	2.05, 2.1, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
	2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 2.85, 2.9, 2.95, 3.0,
	2.95, 2.9, 2.85, 2.8, 2.75, 2.7, 2.65, 2.6, 2.55, 2.5,
	2.45, 2.4, 2.35, 2.3, 2.25, 2.2, 2.15, 2.1, 2.05, 2.0,
	1.95, 1.9, 1.85, 1.8, 1.75, 1.7, 1.65, 1.6, 1.55, 1.5,
	1.45, 1.4, 1.35, 1.3, 1.25, 1.2, 1.15, 1.1, 1.05, 1.0};
dacValue = (uint16_t)((sineWave[index] * MAX_DAC_OUTPUT) / DAC_VREF);
*/
// Represents 1V to 3V and 3V to 1V
static const uint16_t sineWave[MAX_SINE_WAVE_VALUES] = {
	1240, 1302, 1365, 1427, 1489, 1551, 1613, 1675, 1737, 1799, 1861,
	1923, 1985, 2047, 2109, 2171, 2233, 2295, 2357, 2419, 2481, 2543,
	2605, 2667, 2730, 2792, 2854, 2916, 2978, 3040, 3102, 3164, 3226,
	3288, 3350, 3412, 3474, 3536, 3598, 3660, 3722,
	3660, 3598, 3536, 3474, 3412, 3350, 3288, 3226, 3164, 3102,
	3040, 2978, 2916, 2854, 2792, 2730, 2667, 2605, 2543, 2481,
	2419, 2357, 2295, 2233, 2171, 2109, 2047, 1985, 1923, 1861,
	1799, 1737, 1675, 1613, 1551, 1489, 1427, 1365, 1302, 1240};
TimerHandle_t DAC_Timer;
uint8_t dacSineWaveCount = 0;
SemaphoreHandle_t xSemaphore;

// https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void vDAC_CallBack(TimerHandle_t xTimer)
{
	if (xSemaphoreTake(xSemaphore, (TickType_t) 10))
	{
#ifndef PROGRAM_TWO
		LED_BLUE_TOGGLE();
#else
		LED_GREEN_TOGGLE();
#endif
		static uint32_t index = 0;
		Log_integer(STATUS_LEVEL, DAC_CALL_BACK, sineWave[index]);
		DAC_SetBufferValue(DAC_BASEADDR, 0U, sineWave[index]);
		index++;
		if (index == MAX_SINE_WAVE_VALUES)
		{
			index = 0;
			dacSineWaveCount++;
		}
		xSemaphoreGive(xSemaphore);
	}
}

void initDAC_Timer()
{
	DAC_Timer = xTimerCreate("DACTimer", pdMS_TO_TICKS(100), pdTRUE, (void *) 0, vDAC_CallBack);
    if (DAC_Timer == NULL)
    {

    }
    else
    {
    	if (xTimerStart(DAC_Timer, 0) != pdPASS)
    	{

    	}
    }
}

void initDAC0()
{
	dac_config_t dacConfigStruct;

	// Configure the DAC
	dacConfigStruct.referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2;
	dacConfigStruct.enableLowPowerMode = false;
	DAC_GetDefaultConfig(&dacConfigStruct);
	DAC_Init(DAC_BASEADDR, &dacConfigStruct);
	DAC_Enable(DAC_BASEADDR, true);
	DAC_SetBufferReadPointer(DAC_BASEADDR, 0U);
	dacSineWaveCount = 0;
	xSemaphore = xSemaphoreCreateMutex();
}


