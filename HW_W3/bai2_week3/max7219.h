#ifndef MAX7219_H
#define MAX7219_H

#include "stm32f1xx.h"

void MAX7219_Init(void);

void MAX7219_Write(uint8_t address,
                   uint8_t data);

void MAX7219_Clear(void);

void MAX7219_Display(uint8_t data[8]);

#endif
