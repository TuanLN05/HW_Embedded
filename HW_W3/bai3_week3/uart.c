#include "uart.h"

void UART1_Init(void)
{
    RCC->APB2ENR |= (1 << 2);              // Bat clock GPIOA
    RCC->APB2ENR |= (1 << 14);             // Bat clock USART1

    GPIOA->CRH &= ~(0xF << 4);             // Xoa cau hinh PA9
    GPIOA->CRH |=  (0xB << 4);             // PA9 = AF Push-Pull 50MHz

    USART1->CR1 = 0;                        // Reset CR1
    USART1->CR2 = 0;                        // 1 stop bit
    USART1->CR3 = 0;                        // Reset CR3

    USART1->BRR = 0x271;                     // 27MHz, baudrate 115200

    USART1->CR3 |= (1 << 7);                // DMAT = 1, cho phep TX bang DMA
    USART1->CR1 |= (1 << 3);                // TE = 1, bat transmitter
    USART1->CR1 |= (1 << 13);               // UE = 1, bat USART1
}
