#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f1xx.h"

extern volatile uint32_t millis;

void SysTick_Init(void);

#endif
