/*
 * PES Project Three LED Control source code implementation
 * Tristan Duenas
 * References:
 * https://stackoverflow.com/questions/15436060/how-to-get-timestamp-in-c
 */

#include "led_control.h"
#include "timing_control.h"

void led_control(ledStates commandedLED_State)
{
#if defined(FB_RUN) || defined(FB_DEBUG)
	switch (commandedLED_State)
	{
		case RED:
			LED_GREEN_OFF();
			LED_BLUE_OFF();
			LED_RED_ON();
			break;
		case GREEN:
			LED_RED_OFF();
			LED_BLUE_OFF();
			LED_GREEN_ON();
			break;
		case BLUE:
			LED_RED_OFF();
			LED_GREEN_OFF();
			LED_BLUE_ON();
			break;
		case OFF:
			LED_RED_OFF();
			LED_GREEN_OFF();
			LED_BLUE_OFF();
			break;
		default:
			// Do nothing
			break;
	}
#endif
}
