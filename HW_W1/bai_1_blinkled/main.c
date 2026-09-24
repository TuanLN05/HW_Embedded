#include "stm32f1xx.h"

void delay_ms(int time)
{
	while(time)
	{
		SysTick -> CTRL  |= 0x00000005;
		SysTick -> LOAD   = 72000 - 1; 
		SysTick -> VAL    = 0;
		while(!(SysTick -> CTRL & (1 << 16))){
		}
		--time;
	}
}

int main(void)
{
    RCC -> APB2ENR |= (1 << 4);
    GPIOC -> CRH &= ~(0xF << 20);
    GPIOC -> CRH |= (0x3 << 20);//outputpushpull50mhz
    while (1)
    {
     GPIOC->BSRR = (1 << 13);
     delay_ms(100);
     GPIOC->BRR =  (1 << 13);
     delay_ms(100);
    }
}
