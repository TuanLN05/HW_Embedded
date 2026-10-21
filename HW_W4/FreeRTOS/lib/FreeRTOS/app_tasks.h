#ifndef APP_TASKS_H
#define APP_TASKS_H

#include "stm32f103xb.h"
#include "FreeRTOS.h"
#include "task.h"

#ifdef FreeRTOS_debug
void vTask_0_1Hz(void *pvParameters);
void vTask_1Hz(void *pvParameters);
void vTask_10Hz(void *pvParameters);
#endif
typedef struct
{
    uint32_t Pin;
    uint32_t time;
} BlinkTaskParams;

void vTask_blink(void *pvParameters);


#ifdef pwm_debug
void vTask_LedSine(void *pvParameters);
#endif

#endif
