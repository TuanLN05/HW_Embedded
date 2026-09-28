#include "adc.h"

void adc1_init(uint8_t channel)
{
    RCC->APB2ENR |= 1 << 9; // Enable ADC1 clock

    ADC1 -> CR1 |= ADC_CR1_EOCIE; // Enable end of conversion interrupt
    ADC1 -> CR2 |= ADC_CR2_ADON; // Enable ADC1
    
    ADC1 -> SQR1 &= ~(0xF << 20);
    ADC1 -> SQR3 = channel;

    if(channel < 10)
    {
        ADC1 -> SMPR2 |= (0x7 << (channel * 3)); // Set sample time for channel
    }
    else
    {
        ADC1 -> SMPR1 |= (0x7 << ((channel - 10) * 3)); // Set sample time for channel
    }
    ADC1 -> CR2 &= ~(7 << 17);
    ADC1 -> CR2 |= 7 << 17;
    ADC1 -> CR2 |= 1 << 20;

    for(int i = 0; i < 10000; i++); // Delay for ADC stabilization
    ADC1 -> CR2 |= ADC_CR2_ADON; // Start ADC1
    for(int i = 0; i < 1000; i++); // Delay for ADC stabilization

    ADC1 -> CR2 |= 1 << 3;
    while(ADC1 -> CR2 & (1 << 3)); // Wait for calibration to complete

    ADC1 -> CR2 |= 1 << 2;
    while(ADC1 -> CR2 & (1 << 2)); // Wait for calibration to complete
}

uint16_t adc1_read(ADC_TypeDef *ADCx)
{
    ADCx -> SR = 0;
    ADCx -> CR2 |= 1 << 22; // Start conversion
    while(!(ADCx -> SR & (1 << 1))); // Wait for conversion to complete
    return ADCx -> DR; // Return the converted value
}