#include "button.h"

void Button_Init(void)
{
    RCC->APB2ENR |= (1 << 2);              // Bat clock GPIOA

    GPIOA->CRL &= ~(0xF << 0);             // Xoa cau hinh PA0
    GPIOA->CRL |=  (0x8 << 0);             // PA0 = Input Pull-up/Pull-down

    GPIOA->ODR |= (1 << 0);                 // Chon Pull-up
}

uint8_t Button_Read(void)
{
    if ((GPIOA->IDR & (1 << 0)) == 0)      // PA0 = 0 khi nhan nut
    {
        return 1;                           // Dang nhan
    }

    return 0;                               // Khong nhan
}
