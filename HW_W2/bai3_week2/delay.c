#include "delay.h"

void delay_ms(unsigned int ms)
{
    volatile unsigned int i;
    while (ms--)
        for (i = 0; i < 800; i++);         /* ~1 ms á»Ÿ 8 MHz, chá»‰nh láº¡i náº¿u lá»‡ch */
}
