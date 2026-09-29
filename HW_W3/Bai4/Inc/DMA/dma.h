#ifndef DMA_H
#define DMA_H

#include "stm32f103xb.h"

#define DMA_ADC_BUFFER_SIZE 100U
#define DMA_ADC_HALF_SIZE   (DMA_ADC_BUFFER_SIZE / 2U)

extern volatile uint16_t dma_adc_buffer[DMA_ADC_BUFFER_SIZE];

void dma_adc(void);
void DMA1_Channel1_IRQHandler(void);

#endif
