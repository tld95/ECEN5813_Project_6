/*
 *  PES Project Six DSP Control header code implementation
 *	Tristan Duenas
 *	Refereneces:
 *	https://www.sanfoundry.com/c-program-mean-variance-standard-deviation/
 */

#ifndef __DSP_CONTROL_H__
#define __DSP_CONTROL_H__

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "DAC_control.h"
#include "ADC_control.h"
#include "logger.h"

/*
 * Processes ADC raw machine unit data and converts it to voltages.
 * Once in voltage format the max, min, average, and standard deviations of the
 * buffer are calculated.
 */
void processDSP_BufferAndOutputReport(uint16_t* buffer);
// Gets first decimal value of float
uint16_t getFirstVoltageDigit(float f);
// Gets second decimal value of float
uint16_t getSecondVoltageDigit(float f, uint16_t firstDigit);

#endif
