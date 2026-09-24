#include "stm32f1xx.h"
#include "uart.h"
#include "adc.h"
#include "delay.h"

int main(void)
{
    unsigned int adc, mv, sum, i, val, vmin, vmax, vpp;

    RCC->APB2ENR |= 0xFC | (1 << 9) | (1 << 14);   /* GPIO A..F, ADC1, USART1 */

    GPIOA->CRL = 0x44444440;               /* PA0 = analog input */
    GPIOC->CRH = 0x44244444;               /* PC13 = output push-pull 2 MHz */

    adc1_init();
    usart1_init();
    delay_ms(1);                           /* chá»� ADC á»•n Ä‘á»‹nh */

    while (1)
    {
        sum  = 0;
        vmin = 4095;
        vmax = 0;
        for (i = 0; i < 1000; i++)
        {
            val = adc1_read();
            sum += val;
            if (val < vmin) vmin = val;
            if (val > vmax) vmax = val;
        }
        adc = sum / 1000;
        mv  = adc * 3300 / 4095;
        vpp = (vmax - vmin) * 3300 / 4095;

        usart1_sendStr("ADC=");
        usart1_sendInt(adc);
        usart1_sendStr("  V=");
        usart1_sendVolt(mv);
        usart1_sendStr(" V  Vpp=");
        usart1_sendVolt(vpp);
        usart1_sendStr(" V\n\r");

        GPIOC->ODR ^= (1 << 13);           /* Ä‘áº£o LED PC13 */
        delay_ms(1000);                    /* 1 giÃ¢y */
    }
}
