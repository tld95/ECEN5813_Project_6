#include "DAC_control.h"

static const float sineWave[MAX_SINE_WAVE_VALUES] = {
	1.0, 1.05, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4, 1.45, 1.5,
	1.55, 1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2.0,
	2.05, 2.1, 2.15, 2.2, 2.25, 2.3, 2.35, 2.4, 2.45, 2.5,
	2.55, 2.6, 2.65, 2.7, 2.75, 2.8, 2.85, 2.9, 2.95, 3.0,
	2.95, 2.9, 2.85, 2.8, 2.75, 2.7, 2.65, 2.6, 2.55, 2.5,
	2.45, 2.4, 2.35, 2.3, 2.25, 2.2, 2.15, 2.1, 2.05, 2.0,
	1.95, 1.9, 1.85, 1.8, 1.75, 1.7, 1.65, 1.6, 1.55, 1.5,
	1.45, 1.4, 1.35, 1.3, 1.25, 1.2, 1.15, 1.1, 1.05, 1.0};
TimerHandle_t DAC_Timer;
uint32_t index;

// https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void vDAC_CallBack(TimerHandle_t xTimer)
{
	Log_integer(STATUS_LEVEL, MAIN, sineWave[index]);
	index++;
	if (index == MAX_SINE_WAVE_VALUES)
	{
		index = 0;
	}
	uint16_t dacValue = (uint16_t)((sineWave[index] * MAX_DAC_OUTPUT) / DAC_VREF);
	DAC_SetBufferValue(DAC_BASEADDR, 0U, dacValue);
	PRINTF("DAC Value: %d\r\n", dacValue);
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

	index = 0;
}


