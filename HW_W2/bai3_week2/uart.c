#include "stm32f1xx.h"
#include "uart.h"

/* UART1: PA9 TX, 115200 baud @ 8 MHz */
void usart1_init(void)
{
    GPIOA->CRH  = 0x444444B4;              /* PA9 = AF push-pull 50MHz, cÃ²n láº¡i input floating */
    USART1->BRR = 69;                      /* 8 000 000 / 115 200 */
    USART1->CR1 = (1 << 13) | (1 << 3);    /* UE = 1, TE = 1 */
}

void usart1_sendChar(char c)
{
    while ((USART1->SR & (1 << 7)) == 0);  /* chá»� TXE */
    USART1->DR = c;
}

void usart1_sendStr(char *s)
{
    while (*s) usart1_sendChar(*s++);
}

void usart1_sendInt(unsigned int v)
{
    char buf[11];
    int i = 10;
    buf[i] = 0;
    if (v == 0) buf[--i] = '0';
    while (v > 0)
    {
        buf[--i] = '0' + (v % 10);
        v /= 10;
    }
    usart1_sendStr(&buf[i]);
}

void usart1_sendVolt(unsigned int mv)
{
    usart1_sendInt(mv / 1000);
    usart1_sendChar('.');
    if ((mv % 1000) < 100) usart1_sendChar('0');
    if ((mv % 1000) < 10)  usart1_sendChar('0');
    usart1_sendInt(mv % 1000);
}
