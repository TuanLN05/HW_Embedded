#ifndef uart_H
#define uart_H

#include "stm32f103xb.h"

void USART1_IRQHandler(void);
void uart_config(void);
void uartWrite(uint8_t c);
void uartWriteString(const char *str);
uint8_t uartRead(void);

#endif