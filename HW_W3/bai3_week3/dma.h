#ifndef DMA_H
#define DMA_H

#include "stm32f1xx.h"

extern volatile uint8_t dma_uart_busy;

void DMA_UART1_TX_Init(void);
void DMA_UART1_Send(char *data, uint16_t length);
uint8_t DMA_UART1_IsBusy(void);

#endif
