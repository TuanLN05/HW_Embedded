#include "timer.h"

void timer1_init_100hz(void)
{
    /* TIM1 clock is 72 MHz because APB2 runs at 72 MHz. */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    TIM1->CR1 = 0U;
    TIM1->DIER = 0U;
    TIM1->CCER = 0U;
    TIM1->BDTR = 0U;
    TIM1->PSC = 7199U; /* 72 MHz / (7199 + 1) = 10 kHz. */
    TIM1->ARR = 99U;   /* 10 kHz / (99 + 1) = 100 Hz. */
    TIM1->RCR = 0U;

    /* PWM1 produces one TIM1_CC1 rising edge per 10 ms period. */
    TIM1->CCR1 = 50U;
    TIM1->CCMR1 = TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE;

    TIM1->CNT = 0U;
    TIM1->EGR = TIM_EGR_UG;     /* Load PSC and ARR immediately. */
    TIM1->SR = 0U;
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}
