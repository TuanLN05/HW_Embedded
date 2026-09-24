#include "stm32f1xx.h"

int main(void)
{
    RCC->APB2ENR |= (1 << 2);//enable port A
    GPIOA -> CRL &= 0x0;
    GPIOA -> CRL |= 0x88888888; // cau hinh pa0-7 la input
    GPIOA -> CRH &= 0x0;
    GPIOA -> CRH |= 0x33333333;//cau hinh pa8-15 la outputpp
    while (1)
    {
    GPIOA->ODR =
    (GPIOA->ODR  & 0x00FF) |
    (((~GPIOA->IDR) & 0x00FF) << 8); 
    }
}
