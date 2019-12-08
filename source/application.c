/*
 *  PES Project Five application source code implementation
 *	Tristan Duenas
 *	References:
 *	https://www.geeksforgeeks.org/snprintf-c-library/
 */

#include "application.h"

extern circularBuffer rxBuffer;
extern circularBuffer txBuffer;

uint8_t asciiTracker[ASCII_CHARACTERS];

void applicationInit()
{
	memset(asciiTracker, 0, sizeof(uint8_t) * ASCII_CHARACTERS);
}

void processAndDisplayReceivedCharacters()
{
	uint8_t character;
	led_control(BLUE);
	while (checkIfBufferIsEmpty(&rxBuffer) != NO_ERROR)
	{
		__asm("NOP");
	}

	while (removeItem(&rxBuffer, &character) == NO_ERROR)
	{
		// Ignore carriage return, as it used to indicate the end of a string
		if (character != '\r')
		{
			updateASCII_Tracker(character);
		}
	}

	led_control(GREEN);
	delay(50);
	if (character == '\r')
	{
		displayASCII_Tracker();
	}
}

void updateASCII_Tracker(uint8_t character)
{
	if ((character > 0) && (character < ASCII_CHARACTERS))
	{
		asciiTracker[character]++;
	}
}

void displayASCII_Tracker()
{
	for (uint32_t index = 0; index < ASCII_CHARACTERS; index++)
	{
		if (asciiTracker[index] != 0)
		{
			// Referenced https://www.geeksforgeeks.org/snprintf-c-library/
			char buffer[20];
			snprintf(buffer, 7, "%c-%d;", index, asciiTracker[index]);
			Log_string(CUSTOM_FORMAT, DISPLAY_ASCII_TRACKER, buffer);
		}
	}
	Log_newline();
	Log_string(DEBUG_LEVEL, DISPLAY_ASCII_TRACKER, "ASCII Count Printed");
}
