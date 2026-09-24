#include "stm32f1xx.h"
#include "adc.h"

void adc1_init(void)
{
    ADC1->CR2   = 1;                       /* ADON = 1 (power-up) */
    ADC1->SMPR2 = 5;                       /* SMP0 = 101 -> 55.5 chu ká»³ */
    ADC1->SQR3  = 0;                       /* chá»�n kÃªnh 0 */

    ADC1->CR2 |= (1 << 3);                 /* RSTCAL */
    while (ADC1->CR2 & (1 << 3));
    ADC1->CR2 |= (1 << 2);                 /* CAL */
    while (ADC1->CR2 & (1 << 2));
}

unsigned int adc1_read(void)
{
    ADC1->CR2 |= 1;                        /* ADON = 1 láº§n ná»¯a: báº¯t Ä‘áº§u chuyá»ƒn Ä‘á»•i */
    while ((ADC1->SR & (1 << 1)) == 0);    /* chá»� cá»� EOC */
    return ADC1->DR;                       /* Ä‘á»�c DR tá»± xoÃ¡ EOC */
}
