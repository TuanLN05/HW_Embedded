#include "systick.h"

volatile uint32_t millis = 0;

void SysTick_Init(void)
{
    SysTick->LOAD = 72000 - 1;               // 72MHz / 72000 = 1kHz = 1ms
    SysTick->VAL = 0;                       // Xoa gia tri counter
    SysTick->CTRL = 0x00000007;             // Clock CPU + Interrupt + Enable
}

void SysTick_Handler(void)
{
    millis++;                               // Tang moi 1ms
}
