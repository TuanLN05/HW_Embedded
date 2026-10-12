#ifndef APP_TASKS_H
#define APP_TASKS_H

#include "stm32f103xb.h"
#include "FreeRTOS.h"
#include "task.h"

void vTask_0_1Hz(void *pvParameters);
void vTask_1Hz(void *pvParameters);
void vTask_10Hz(void *pvParameters);
void vTask_LedSine(void *pvParameters);

#endif
