#ifndef UART_H
#define UART_H

#include "stm32f1xx.h"
#include <stdint.h>

#define BUFFER_SIZE 128

void UART1_Init(void);
void UART1_SendChar(char data);
void UART1_SendString(const char *str);

#endif
