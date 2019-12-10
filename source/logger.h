/*
 * PES Project Three display logger header code implementation
 * Tristan Duenas
 * References:
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "fsl_debug_console.h"
#include "functions_enum_list.h"
#include "timing_control.h"

typedef enum logStatus
{
	DISABLED = 0,
	ENABLED = 1
} logStatus;

typedef enum logLevel
{
	TEST_LEVEL = 0,
	DEBUG_LEVEL = 1,
	STATUS_LEVEL = 2,
	CUSTOM_FORMAT = 3,
} logLevel;

// Enables logging
void Log_enable();
// Disables logging
void Log_disable();
// Returns current logging enabled/disabled status
logStatus Log_status();
// Logs a block of data from memory
void Log_data(logLevel level, Function_Names funcName, uint8_t *address, size_t length);
// Logs a string
void Log_string(logLevel level, Function_Names funcName, char *string);
// Logs an integer
void Log_integer(logLevel level, Function_Names funcName, size_t integer);
// Logs a float
void Log_float(logLevel level, Function_Names funcName, float fpValue);
// Logs newline
void Log_newline();

#endif
