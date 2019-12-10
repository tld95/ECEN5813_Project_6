/*
 *  PES Project Six Timing Control header code implementation
 *	Tristan Duenas
 *	References:
 *	https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html
 */

#ifndef __TIMING_CONTROL_H__
#define __TIMING_CONTROL_H__

#include <stdio.h>
#include <stdint.h>
#include "clock_config.h"
#include "MKL25Z4.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"

/*
 * Time for timestamp is now updated as a result of FREERTOS timer
 * that updates every millisecond.
 */
void getTimeStamp(char* timeStamp);
// Timer call back to updated global time in milliseconds since start of program
void vTimerCallBack(TimerHandle_t xTimer);
// initialization of logger timer
void initLoggerTimer();

#endif
