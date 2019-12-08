/*
 *  PES Project Five application header code implementation
 *	Tristan Duenas
 *	References:
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "fsl_debug_console.h"
#include "logger.h"
#include "uart0_control.h"
#include "circular_buffer.h"
#include "timing_control.h"

#define ASCII_CHARACTERS 128

// Initialize ASCII Tracker array
void applicationInit();

// Process received characters
// \r or carriage return indicates end of string entered
void processAndDisplayReceivedCharacters();

// Update ASCII Tracker array with character read in
void updateASCII_Tracker(uint8_t character);

// Display ASCII tracker
void displayASCII_Tracker();

#endif
