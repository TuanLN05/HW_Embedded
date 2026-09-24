#include "systik.h"
#include "setled.h"

volatile uint32_t led1 = 0;
volatile uint32_t led2 = 0;
volatile uint32_t led3 = 0;
void SysTick_Init(void){
     SysTick -> LOAD = 72000 - 1;
     SysTick -> VAL = 0;
     SysTick->CTRL = (1 << 2) | (1 << 1) | (1 << 0);
}

void SysTick_Handler(void){
     led1++; 
     led2++;
     led3++;
     if(led1 >= 5000){
     Led1_Toggle();
     led1 = 0;
     }
     if(led2 >= 500)
    {
     led2 = 0;
     Led2_Toggle();
    }
    if(led3 >= 50)
    {
    led3 = 0;
    Led3_Toggle(); 
    }
}
