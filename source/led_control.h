/*
 *  PES Project Three LED Control header code implementation
 *	Tristan Duenas
 */

#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__

#include "logger.h"

#if defined(FB_RUN) || defined(FB_DEBUG)
#include "board.h"
#include "fsl_debug_console.h"
#endif

typedef enum ledStates
{
	RED,
	GREEN,
	BLUE,
	OFF,
} ledStates;

// Provides the functionality of commanding the board's LED to GREEN, RED, BLUE, or OFF.
void led_control(ledStates commandedLED_State);

#endif
