/*
 * PES Project Six Timing Control source code implementation
 * Tristan Duenas
 * Referenced:
 * https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
 */

#include "timing_control.h"

uint32_t time = 0;
TimerHandle_t loggerTimer;

// https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void vTimerCallBack(TimerHandle_t xTimer)
{
	time++;
}

// https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
void initLoggerTimer()
{
    loggerTimer = xTimerCreate("LoggerTimer", pdMS_TO_TICKS(1), pdTRUE, (void *) 0, vTimerCallBack);
    if (loggerTimer == NULL)
    {

    }
    else
    {
    	if (xTimerStart(loggerTimer, 0) != pdPASS)
    	{

    	}
    }
}

void getTimeStamp(char* timeStamp)
{
	uint32_t hours = time / 3600000L;
	uint32_t minutes = (time - (hours * 3600000)) / 60000L;
	uint32_t seconds = (time - (hours * 3600000) - (minutes * 60000)) / 1000;
	uint32_t n = (time - (hours * 3600000) - (minutes * 60000) - (seconds * 1000));

	// Referenced https://www.geeksforgeeks.org/snprintf-c-library/
	char buf[15];
	snprintf(buf, 15, "%d:%d:%d:%d", hours, minutes, seconds, n);
	strcpy(timeStamp, buf);
}
