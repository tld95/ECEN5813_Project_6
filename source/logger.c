/*
 * PES Project Four display logger source code implementation
 * Tristan Duenas
 * References:
 * https://stackoverflow.com/questions/16370673/how-to-print-32-bit-value-complete
 */

#include "logger.h"

static uint8_t logEnabled = 0;

void Log_enable()
{
	logEnabled = ENABLED;
}

void Log_disable()
{
	logEnabled = DISABLED;
}

logStatus Log_status()
{
	return logEnabled;
}

void Log_data(logLevel level, Function_Names funcName, uint8_t *address, size_t length)
{
	if (Log_status() == ENABLED)
	{
		if (level == TEST_LEVEL)
		{
#ifdef TEST_FLAG
			PRINTF("Test:\r\n", level);
#endif
		}
		else if (level == DEBUG_LEVEL)
		{
#ifdef DEBUG_FLAG
			PRINTF("Debug:\r\n");
#endif
		}
		else if (level == STATUS_LEVEL)
		{
#ifdef STATUS_FLAG
			PRINTF("Status:\r\n");
#endif
		}
		else
		{
			// Do nothing
		}


#ifdef DEBUG_FLAG
		char nameString[MAX_NAME_LENGTH];
		getFunctionName(funcName, nameString);
		PRINTF("%s:\r\n", nameString);
		// Referenced https://stackoverflow.com/questions/16370673/how-to-print-32-bit-value-complete
		PRINTF("Address: 0x%08X ", (uint32_t*)address);
		PRINTF("Value: 0x");

		for (uint32_t index = 0; index < length; index++)
		{
			PRINTF("%02X", address[index]);
		}
		PRINTF("\r\n");
#endif
	}
}

void Log_string(logLevel level, Function_Names funcName, char *string)
{
	if (Log_status() == ENABLED)
	{
		if (level == TEST_LEVEL)
		{
#ifdef TEST_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Test: %s: %s %s\r\n", nameString, string, timeStamp);
#endif
		}
		else if (level == DEBUG_LEVEL)
		{
#ifdef DEBUG_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Debug: %s: %s %s\r\n", nameString, string, timeStamp);
#endif
		}
		else if (level == STATUS_LEVEL)
		{
#ifdef STATUS_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Status: %s: %s %s\r\n", nameString, string, timeStamp);
#endif
		}
		else if (level == CUSTOM_FORMAT)
		{
			PRINTF("%s", string);
		}
		else
		{
			// Do nothing
		}
	}
}

void Log_integer(logLevel level, Function_Names funcName, size_t integer)
{
	if (Log_status() == ENABLED)
	{
		if (level == TEST_LEVEL)
		{
#ifdef TEST_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Test: %s: %d %s\r\n", nameString, integer, timeStamp);
#endif
		}
		else if (level == DEBUG_LEVEL)
		{
#ifdef DEBUG_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Debug: %s: %d %s\r\n", nameString, integer, timeStamp);
#endif
		}
		else if (level == STATUS_LEVEL)
		{
#ifdef STATUS_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Status: %s: %d %s\r\n", nameString, integer, timeStamp);
#endif
		}
		else
		{
			// Do nothing
		}
	}
}

void Log_float(logLevel level, Function_Names funcName, float fpValue)
{
	if (Log_status() == ENABLED)
	{
		if (level == TEST_LEVEL)
		{
#ifdef TEST_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Test: %s: %f %s\r\n", nameString, fpValue, timeStamp);
#endif
		}
		else if (level == DEBUG_LEVEL)
		{
#ifdef DEBUG_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Debug: %s: %f %s\r\n", nameString, fpValue, timeStamp);
#endif
		}
		else if (level == STATUS_LEVEL)
		{
#ifdef STATUS_FLAG
			char timeStamp[15];
			getTimeStamp(timeStamp);
			char nameString[MAX_NAME_LENGTH];
			getFunctionName(funcName, nameString);
			PRINTF("Status: %s: %f %s\r\n", nameString, fpValue, timeStamp);
#endif
		}
		else
		{
			// Do nothing
		}
	}
}

void Log_newline()
{
	PRINTF("\r\n");
}
