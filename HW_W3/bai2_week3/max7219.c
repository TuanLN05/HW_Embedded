#include "max7219.h"
#include "spi.h"


void MAX7219_Write(uint8_t address,
                   uint8_t data)
{
    GPIOA->BRR = (1 << 4);//cs = 0

    SPI1_SendByte(address);
    SPI1_SendByte(data);
    GPIOA->BSRR = (1 << 4);// cs = 1 chot du lieu
}


void MAX7219_Clear(void)
{
    uint8_t i;

    for (i = 1; i <= 8; i++)
    {
        MAX7219_Write(i, 0x00);
    }
}


void MAX7219_Init(void)
{
    MAX7219_Write(0x09, 0x00);//decode mode 0
    MAX7219_Write(0x0A, 0x05);//intencity
    MAX7219_Write(0x0B, 0x07);//scan limit 7 hang
    MAX7219_Write(0x0C, 0x01);//tat thanh ghi
    MAX7219_Write(0x0F, 0x00);//display test off

    MAX7219_Clear();
}


void MAX7219_Display(uint8_t data[8])
{
    uint8_t i;

    for (i = 0; i < 8; i++)
    {
        MAX7219_Write(i + 1, data[i]);
    }
}
