#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "logger.h"
#include "fsl_adc16.h"
#include "math.h"

#define ADC16_BASE ADC0
#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL 0U /*PTE20, ADC0_SE0 */

void vADC_CallBack(TimerHandle_t xTimer);
void initADC_Timer();
void initADC0();
