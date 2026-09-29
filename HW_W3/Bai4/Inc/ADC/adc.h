#ifndef ADC_H
#define ADC_H

#include "stm32f103xb.h"

void adc_delay(volatile uint32_t count);
void adc1_init(uint8_t channel);
uint16_t adc1_read(void);

#endif
