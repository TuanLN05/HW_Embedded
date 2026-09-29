#include "uart.h"

#define UART_RX_BUFFER_SIZE 32U
static volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0U;
void USART1_IRQHandler(void)
{
    if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        uint8_t data = uartRead();
        uint8_t next = (uint8_t)((rx_head + 1U) % UART_RX_BUFFER_SIZE);

        rx_buffer[rx_head] = data;
        rx_head = next;
    }
}

void uart_config(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    /* PA9: USART1 TX, alternate-function push-pull. */
    GPIOA->CRH &= ~(0xFU << 4);
    GPIOA->CRH |= (0xBU << 4);

    /* PA10: USART1 RX, input pull-up. */
    GPIOA->CRH &= ~(0xFU << 8);
    GPIOA->CRH |= (0x8U << 8);
    GPIOA->BSRR = GPIO_BSRR_BS10;

    USART1->CR1 = 0U;
    USART1->BRR = 7500U; /* 72 MHz / 9600 baud, oversampling by 16. */
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE |
                  USART_CR1_RE | USART_CR1_RXNEIE;

    NVIC_ClearPendingIRQ(USART1_IRQn);
    NVIC_EnableIRQ(USART1_IRQn);
}

void uartWrite(uint8_t c)
{
    while ((USART1->SR & USART_SR_TXE) == 0U)
        ;
    USART1->DR = c;
}

void uartWriteString(const char *str)
{
    while (*str != '\0')
        uartWrite((uint8_t)*str++);
}
uint8_t uartRead(void)
{
    if (((USART1->SR) & USART_SR_RXNE) != 0)
        return (uint8_t)USART1->DR;
    else
        return 0;
}