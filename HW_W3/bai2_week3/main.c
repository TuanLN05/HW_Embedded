#include "stm32f1xx.h"
#include "spi.h"
#include "max7219.h"


int main(void)
{
    uint8_t Dac[8] =
    {
        0xFF,
        0x66,
        0xFF,
        0xFF,
        0x7E,
        0x3C,
        0x18,
        0xFF
    };

    SPI1_Init();

    MAX7219_Init();

    MAX7219_Display(Dac);

    while (1)
    {
    }
}
