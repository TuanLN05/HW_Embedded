#include "uart.h"

void UART1_Init(void)
{
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 14);

    GPIOA->CRH &= 0xFFFFF00F;
    GPIOA->CRH |= 0x000004B0;

    USART1->BRR = 0x45;

    USART1->CR1 = 0;

    USART1->CR1 |= (1 << 3);
    USART1->CR1 |= (1 << 2);
    USART1->CR1 |= (1 << 13);
}

void UART1_SendChar(char data)
{
    while (!(USART1->SR & (1 << 7)));

    USART1->DR = data;
}

void UART1_SendString(const char *str)
{
    while (*str)
    {
        UART1_SendChar(*str++);
    }
}
