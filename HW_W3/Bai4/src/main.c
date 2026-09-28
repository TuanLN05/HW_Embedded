#include "adc.h"
#include "stdint.h"
int main(void)
{
    adc1_init(0); // Initialize ADC1 on channel 0

    while (1)
    {
        uint16_t adc_value = adc1_read(ADC1); // Read ADC value from ADC1
        // Process the adc_value as needed
    }
}