#include "adc.h"

void adc_delay(volatile uint32_t count)
{
    while (count > 0U)
        count--;
}

void adc1_init(uint8_t channel)
{
    /* PCLK2 = 72 MHz, ADC clock = PCLK2 / 6 = 12 MHz. */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_ADCPRE) |
                RCC_CFGR_ADCPRE_DIV6;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_ADC1EN;

    /* PB0 is ADC1 channel 8: analog input (MODE = 00, CNF = 00). */
    GPIOB->CRL &= ~(0xFUL << 0);

    ADC1->CR1 = 0U;
    ADC1->CR2 = 0U;

    ADC1->SQR1 &= ~ADC_SQR1_L; /* One regular conversion. */
    ADC1->SQR3 = channel;      /* First conversion = selected channel. */

    if (channel <= 9U)
    {
        ADC1->SMPR2 &= ~(7UL << (channel * 3U));
        ADC1->SMPR2 |=  (7UL << (channel * 3U));
    }
    else
    {
        uint8_t offset = channel - 10U;
        ADC1->SMPR1 &= ~(7UL << (offset * 3U));
        ADC1->SMPR1 |=  (7UL << (offset * 3U));
    }

    /* Regular conversion starts on the internal TIM1_CC1 event. */
    ADC1->CR2 &= ~ADC_CR2_EXTSEL;
    ADC1->CR2 |= ADC_CR2_EXTSEL_TIM1_CC1 | ADC_CR2_EXTTRIG;

    adc_delay(10000U);

    ADC1->CR2 |= ADC_CR2_ADON;
    adc_delay(1000U);

    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while ((ADC1->CR2 & ADC_CR2_RSTCAL) != 0U)
        ;

    ADC1->CR2 |= ADC_CR2_CAL;
    while ((ADC1->CR2 & ADC_CR2_CAL) != 0U)
        ;
}

uint16_t adc1_read(void)
{
    ADC1->SR = 0U;
    ADC1->CR2 = (ADC1->CR2 & ~ADC_CR2_EXTSEL) |
                ADC_CR2_EXTSEL_SWSTART | ADC_CR2_EXTTRIG;
    ADC1->CR2 |= ADC_CR2_SWSTART;

    while ((ADC1->SR & ADC_SR_EOC) == 0U)
        ;

    return (uint16_t)ADC1->DR;
}
