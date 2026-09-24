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
  RCC->APB2ENR |= (1<< 2);
  GPIOA -> CRL &= 0x0;
  GPIOA -> CRL = 0x33333333;

    while (1)
    {
    int i;
    for(i = 0; i < 8; i++){
    GPIOA-> BSRR = (1 << i);
    delay_ms(100);
       }
    delay_ms(200);
    for(i = 7;i >= 0; i--){
    GPIOA -> BRR= (1 << i);
    delay_ms(100);
       }
    delay_ms(200); 
    }
}
