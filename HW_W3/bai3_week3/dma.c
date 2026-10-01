#include "dma.h"

volatile uint8_t dma_uart_busy = 0;

void DMA_UART1_TX_Init(void)
{
    RCC->AHBENR |= (1 << 0);                       // Bat clock DMA1

    DMA1_Channel4->CCR &= ~(1 << 0);              // Tat DMA1 Channel 4

    DMA1_Channel4->CPAR = (uint32_t)&USART1->DR;  // Dia chi dich = USART1 DR
    DMA1_Channel4->CMAR = 0;                      // Chua gan buffer
    DMA1_Channel4->CNDTR = 0;                     // Chua gui byte nao

    DMA1_Channel4->CCR = 0;                       // Xoa cau hinh Channel 4
    DMA1_Channel4->CCR |= (1 << 4);               // DIR = 1, Memory -> Peripheral
    DMA1_Channel4->CCR |= (1 << 7);               // MINC = 1, tang dia chi RAM
    DMA1_Channel4->CCR |= (1 << 12);              // Priority = Medium
    DMA1_Channel4->CCR |= (1 << 1);               // TCIE = 1, ngat khi gui xong

    DMA1->IFCR = (0xF << 12);                     // Xoa tat ca flag Channel 4

    NVIC->ISER[0] |= (1 << 14);                   // Bat ngat DMA1 Channel 4
}

void DMA_UART1_Send(char *data, uint16_t length)
{
    if (dma_uart_busy == 1)                       // Neu DMA dang gui
    {
        return;                                   // Khong khoi dong lai DMA
    }

    if (length == 0)                              // Neu khong co du lieu
    {
        return;
    }

    dma_uart_busy = 1;                            // Danh dau DMA dang ban

    DMA1_Channel4->CCR &= ~(1 << 0);              // Tat DMA truoc khi cau hinh
    DMA1->IFCR = (0xF << 12);                     // Xoa flag cu

    DMA1_Channel4->CMAR = (uint32_t)data;         // Dia chi buffer trong RAM
    DMA1_Channel4->CNDTR = length;                // So byte can gui

    DMA1_Channel4->CCR |= (1 << 0);               // Bat DMA
}

uint8_t DMA_UART1_IsBusy(void)
{
    return dma_uart_busy;                         // Tra ve trang thai DMA
}

void DMA1_Channel4_IRQHandler(void)
{
    if (DMA1->ISR & (1 << 13))                    // TCIF4 = 1, gui xong
    {
        DMA1_Channel4->CCR &= ~(1 << 0);          // Tat Channel 4
        DMA1->IFCR = (0xF << 12);                 // Xoa flag Channel 4
        dma_uart_busy = 0;                        // DMA da ranh
    }

    if (DMA1->ISR & (1 << 15))                    // TEIF4 = 1, loi DMA
    {
        DMA1_Channel4->CCR &= ~(1 << 0);          // Tat DMA
        DMA1->IFCR = (0xF << 12);                 // Xoa flag loi
        dma_uart_busy = 0;                        // Cho phep gui lai
    }
}
