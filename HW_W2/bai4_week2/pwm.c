#include "pwm.h"

void PWM_TIM2_Init(void){
     RCC -> APB2ENR |= (1 << 2); //bat clock GPIOA
     RCC -> APB1ENR |= (1 << 0);//TIM2 clock
     
     GPIOA -> CRL &= ~(0x0000FFFF << 0);
     GPIOA -> CRL |= (0x0000BBBB << 0);//alternate PP
     
     //timer
     TIM2 -> PSC = 72 - 1;
     TIM2 -> ARR = 1000 -1;
     
     //Channel 1
     TIM2->CCMR1 &= ~(7 << 4);
     TIM2->CCMR1 |=  (6 << 4);
     TIM2->CCMR1 |= (1 << 3);//OC1PE
     TIM2->CCER |= (1 << 0);//CC1E
     TIM2->CR1 |= (1 << 7);//ARPE
     TIM2->CCR1 = 100; //10%
     TIM2->CR1 |= (1 << 0);
     
     //Channel 2
     TIM2 -> CCMR1 &= ~(7 << 12);
     TIM2 -> CCMR1 |= (6 << 12);
     TIM2 -> CCMR1 |= (1 << 11);//OC2PE
     TIM2 -> CCER |= (1 << 4);//CC2E
     TIM2 -> CR1 |= (1 << 7); //APRE
     TIM2 -> CCR2 = 300;//30%
     TIM2 -> CR1 |= (1 << 0);
     
     //Channel 3
     TIM2 -> CCMR2 &= ~(7 << 4);
     TIM2 -> CCMR2 |= (6 << 4);
     TIM2 -> CCMR2 |= (1 << 3);//OC3PE
     TIM2 -> CCER |= (1 << 8);//CC3E
     TIM2 -> CR1 |= (1 << 7);//APRE 
     TIM2 -> CCR3 = 500;//50%
     TIM2 -> CR1 |= (1 << 0);
   
     //Channel 4
     TIM2 -> CCMR2 &= ~(7 << 12);
     TIM2 -> CCMR2 |= (6 << 12);
     TIM2 -> CCMR2 |= (1 << 11);
     TIM2 -> CCER |= (1 << 12);
     TIM2 -> CR1 |= (1 << 7);
     TIM2 -> CCR4 = 700;
     TIM2 -> CR1 |= (1 << 0);
} 
