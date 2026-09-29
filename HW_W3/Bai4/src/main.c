#include "adc.h"
#include "dma.h"
#include "pwm.h"
#include "timer.h"
#include "uart.h"

int main(void)
{
    uart_config();
    pwm_config();         /* PA0 = TIM2_CH1 PWM output for the LED. */
    pwm_set_percent(0U);
    pwm_turn_on();
    adc1_init(8U);       /* PB0 = ADC1 channel 8. */
    dma_adc();           /* DMA must be ready before ADC triggers begin. */
    timer1_init_100hz();

    while (1)
    {
        /* ADC sampling, RAM storage and UART transmission use hardware/IRQs. */
    }
}
