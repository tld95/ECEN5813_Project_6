#include "ADC_control.h"

TimerHandle_t ADC_Timer;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;

// https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void vADC_CallBack(TimerHandle_t xTimer)
{
    ADC16_SetChannelConfig(ADC16_BASE, ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(ADC16_BASE, ADC16_CHANNEL_GROUP)))
    {
    }
    PRINTF("ADC Value: %d\r\n", ADC16_GetChannelConversionValue(ADC16_BASE, ADC16_CHANNEL_GROUP));
}

void initADC_Timer()
{
	ADC_Timer = xTimerCreate("ADCTimer", pdMS_TO_TICKS(100), pdTRUE, (void *) 0, vADC_CallBack);
    if (ADC_Timer == NULL)
    {

    }
    else
    {
    	if (xTimerStart(ADC_Timer, 0) != pdPASS)
    	{

    	}
    }
}

void initADC0()
{
	// Configure the ADC
	adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
	adc16ConfigStruct.clockSource = kADC16_ClockSourceAsynchronousClock;
	adc16ConfigStruct.enableAsynchronousClock = true;
	adc16ConfigStruct.clockDivider = kADC16_ClockDivider8;
	adc16ConfigStruct.resolution = kADC16_ResolutionSE12Bit;
	adc16ConfigStruct.longSampleMode = kADC16_LongSampleDisabled;
	adc16ConfigStruct.enableHighSpeed = false;
	adc16ConfigStruct.enableLowPower = false;
	adc16ConfigStruct.enableContinuousConversion = false;
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	ADC16_Init(ADC16_BASE, &adc16ConfigStruct);
	ADC16_EnableHardwareTrigger(ADC16_BASE, false); /* Make sure the software trigger is used. */
    adc16ChannelConfigStruct.channelNumber = ADC16_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
}