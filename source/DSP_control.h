#ifndef __DSP_CONTROL__
#define __DSP_CONTROL__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "DAC_control.h"
#include "ADC_control.h"
#include "logger.h"

void processDSP_BufferAndOutputReport(uint16_t* buffer);
void initDSP();
uint16_t getFirstVoltageDigit(float f);
uint16_t getSecondVoltageDigit(float f, uint16_t firstDigit);

#endif
