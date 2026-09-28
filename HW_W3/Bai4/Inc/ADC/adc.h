#ifndef adc_H
#define adc_H

#include "stm32f103xb.h"

void adc1_init(uint8_t channel);
uint16_t adc1_read(void);

#endif