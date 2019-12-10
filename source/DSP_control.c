#include "DSP_control.h"

void processDSP_BufferAndOutputReport(uint16_t* buffer)
{
	float maxVoltage = 1.0;
	float minVoltage = 3.0;
	float voltageSum = 0.0;
	float voltageSumVariance = 0.0;
	float averageVoltage = 0.0;
	float variance = 0.0;
	float standardDeviation = 0.0;
	uint16_t voltageBuffer[MAX_SINE_WAVE_VALUES];
	memset(&voltageBuffer, 0, sizeof(voltageBuffer));

	for (uint32_t index = 0; index < MAX_SINE_WAVE_VALUES; index++)
	{
		// voltage = (dspBuffer[index] * 3.3V) / 4095
		float voltage = (buffer[index] * DAC_VREF) / (MAX_DAC_OUTPUT);
		voltageBuffer[index] = voltage;
		if (voltage > maxVoltage)
		{
			maxVoltage = voltage;
		}
		if (voltage < minVoltage)
		{
			minVoltage = voltage;
		}

		voltageSum += voltage;
	}
	averageVoltage = voltageSum / MAX_SINE_WAVE_VALUES;


	// Referenced from https://www.sanfoundry.com/c-program-mean-variance-standard-deviation/
	// Variance calculation
	for (uint16_t index = 0; index < MAX_SINE_WAVE_VALUES; index++)
	{
		voltageSumVariance = voltageSumVariance + pow((voltageBuffer[index] - averageVoltage), 2);
	}
	variance = voltageSumVariance / MAX_SINE_WAVE_VALUES;
	standardDeviation = sqrt(variance);

	char buf[150];
	uint16_t maxVoltageFirstDigit = getFirstVoltageDigit(maxVoltage);
	uint16_t maxVoltageSecondDigit = getSecondVoltageDigit(maxVoltage, maxVoltageFirstDigit);
	uint16_t minVoltageFirstDigit = getFirstVoltageDigit(minVoltage);
	uint16_t minVoltageSecondDigit = getSecondVoltageDigit(minVoltage, minVoltageFirstDigit);
	uint16_t averageVoltageFirstDigit = getFirstVoltageDigit(averageVoltage);
	uint16_t averageVoltageSecondDigit = getSecondVoltageDigit(averageVoltage, averageVoltageFirstDigit);
	uint16_t standardDeviationFirstDigit = getFirstVoltageDigit(standardDeviation);
	uint16_t standardDeviationSecondDigit = getSecondVoltageDigit(standardDeviation, standardDeviationFirstDigit);
	snprintf(buf, 100, "max voltage: %d.%d, min voltage: %d.%d, average voltage %d.%d standard deviation %d.%d\n\r", maxVoltageFirstDigit, maxVoltageSecondDigit, minVoltageFirstDigit,
			minVoltageSecondDigit, averageVoltageFirstDigit, averageVoltageSecondDigit, standardDeviationFirstDigit, standardDeviationSecondDigit);
	Log_string(STATUS_LEVEL, DSP_PROCESS_REPORT, buf);
}

uint16_t getFirstVoltageDigit(float f)
{
	return (uint16_t)((f * 100)/100);
}

uint16_t getSecondVoltageDigit(float f, uint16_t firstDigit)
{
	return (uint16_t)(((f * 100) - (firstDigit * 100))/10);
}

void initDSP()
{
}
