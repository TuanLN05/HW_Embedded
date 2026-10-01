#include "spi.h"

void SPI1_Init(void)
{
    RCC->APB2ENR |= (1 << 2);//clock gpioa
    RCC->APB2ENR |= (1 << 12);//clock spi1

    GPIOA->CRL &= ~(0xF << 16);
    GPIOA->CRL |=  (0x3 << 16);//pa4= cs outputpp50mhz

    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |=  (0xB << 20);//pa5 clk alternate funcion pp 50mhz

    GPIOA->CRL &= ~(0xF << 24);
    GPIOA->CRL |=  (0x4 << 24);//pa 6 miso input floating

    GPIOA->CRL &= ~(0xF << 28);
    GPIOA->CRL |=  (0xB << 28);//pa7 mosi alternate funcion pp 50mhz

    GPIOA->BSRR = (1 << 4);//cs  = 1

    SPI1->CR1 = 0;

    SPI1->CR1 |= (1 << 2);//master

    SPI1->CR1 |= (2 << 3);//pclk / 8

    SPI1->CR1 &= ~(1 << 1);
    SPI1->CR1 &= ~(1 << 0);
    SPI1->CR1 &= ~(1 << 7);
    SPI1->CR1 |= (1 << 9);
    SPI1->CR1 |= (1 << 8);
    SPI1->CR1 &= ~(1 << 11);
    SPI1->CR1 |= (1 << 6);
}


void SPI1_SendByte(uint8_t data)
{
    volatile uint8_t temp;
    while (!(SPI1->SR & (1 << 1)))//cho txne  = 1
    {
    }

    *((volatile uint8_t *)&SPI1->DR) = data;

    while (!(SPI1->SR & (1 << 0)))//cho rxne = 1
    {
    }

    temp = *((volatile uint8_t *)&SPI1->DR);

    (void)temp;

    while (SPI1->SR & (1 << 7)) // cho spi het ban
    {
    }
}
