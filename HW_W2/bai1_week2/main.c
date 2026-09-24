#include "stm32f1xx.h"
#include "uart.h"

int main(void)
{
    char rx_buffer[BUFFER_SIZE];
    uint16_t rx_index = 0;
    char data;

    UART1_Init();

    UART1_SendString("UART Ready\r\n");

    while (1)
    {
        if (USART1->SR & (1 << 5))
        {
            data = (char)USART1->DR;

            if (data == '!')
            {
                rx_buffer[rx_index] = '\0';

                UART1_SendString("HTN-01 Nhom 03: ");
                UART1_SendString(rx_buffer);
                UART1_SendString("\r\n");

                rx_index = 0;
            }
            else
            {
                if (rx_index < BUFFER_SIZE - 1)
                {
                    rx_buffer[rx_index++] = data;
                }
                else
                {
                    rx_index = 0;
                }
            }
        }
    }
}
