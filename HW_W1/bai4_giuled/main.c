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
    RCC->APB2ENR |= (1 << 2);
    GPIOA -> CRL &= 0xFFFFFF00; //reset pa0-1;
    GPIOA -> CRL |= 0x00000038; //pa0 input pa1 outputpp
    while (1)
    {
    if((GPIOA -> IDR & 1) == 0){
     delay_ms(10); //chong doi nut button
      GPIOA->ODR ^=(1 << 1);
      while((GPIOA -> IDR & 1) == 0);
      delay_ms(10);  
      }
    }
}  
