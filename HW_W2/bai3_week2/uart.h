#ifndef UART_H
#define UART_H

void usart1_init(void);
void usart1_sendChar(char c);
void usart1_sendStr(char *s);
void usart1_sendInt(unsigned int v);
void usart1_sendVolt(unsigned int mv);

#endif
