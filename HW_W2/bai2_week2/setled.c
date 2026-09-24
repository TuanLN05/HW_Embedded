#include "setled.h"

void Led_Init(void){
     RCC -> APB2ENR |= (1 << 2);
     GPIOA -> CRL &= ~0x00000FFF;
     GPIOA -> CRL |= 0x00000333;
     GPIOA -> BRR |= 0x00000111;
}

void Led1_Toggle(void){
     GPIOA -> ODR ^= (1 << 0);
}

void Led2_Toggle(void){
     GPIOA -> ODR ^= (1 << 1);
}

void Led3_Toggle(void){
     GPIOA -> ODR ^= (1 << 2);
}
