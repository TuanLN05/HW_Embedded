#include "stm32f1xx.h"
#include "uart.h"
#include "dma.h"
#include "button.h"
#include "systick.h"
#include "clock.h"

static char tx_buffer[64];

uint16_t Add_String(char *buffer, uint16_t index, const char *str)
{
    while (*str != '\0')                           // Lap den het chuoi
    {
        buffer[index++] = *str++;                  // Copy tung ky tu vao buffer
    }

    return index;
}


uint16_t Add_Number(char *buffer, uint16_t index, uint32_t number)
{
    char temp[10];                                 // Buffer tam cho so
    uint8_t i = 0;                                 // Vi tri tam

    if (number == 0)                               // Truong hop gia tri = 0
    {
        buffer[index++] = '0';                     // Them ky tu 0
        return index;
    }

    while (number > 0)                             // Tach tung chu so
    {
        temp[i++] = (number % 10) + '0';           // Doi so thanh ASCII
        number /= 10;                              // Bo chu so vua tach
    }

    while (i > 0)                                  // Dao nguoc lai thu tu
    {
        buffer[index++] = temp[--i];               // Dua vao buffer chinh
    }

    return index;
}


uint16_t Create_Message(uint32_t count)
{
    uint16_t index = 0;                            // Bat dau tu dau buffer

    index = Add_String(tx_buffer, index, "He_thong_nhung_01:"); // ID lop
    index = Add_String(tx_buffer, index, "Nhom_03");              // ID nhom
    index = Add_String(tx_buffer, index, ":BTN:");            // Noi dung co dinh
    index = Add_Number(tx_buffer, index, count);               // Them so lan nhan

    tx_buffer[index++] = '\r';                     // Carriage Return
    tx_buffer[index++] = '\n';                     // New Line

    return index;                                  // Tra ve tong so byte
}


int main(void)
{
    uint32_t button_count = 0;                     // Dem so lan nhan nut
    uint8_t raw_button = 0;                        // Trang thai nut hien tai
    uint8_t last_raw_button = 0;                   // Trang thai doc lan truoc
    uint8_t stable_button = 0;                     // Trang thai sau chong doi
    uint32_t debounce_time = 0;                    // Moc thoi gian chong doi
    uint16_t length = 0;                           // Do dai ban tin
    Clock_Init_72MHz();
    UART1_Init();                                  // Khoi tao USART1 TX
    DMA_UART1_TX_Init();                           // Khoi tao DMA1 Channel 4
    Button_Init();                                 // Khoi tao PA0
    SysTick_Init();                                // Khoi tao SysTick 1ms

    while (1)
    {
        raw_button = Button_Read();                // Doc trang thai PA0

        if (raw_button != last_raw_button)         // Neu trang thai vua thay doi
        {
            last_raw_button = raw_button;          // Luu trang thai moi
            debounce_time = millis;                // Bat dau dem thoi gian debounce
        }

        if ((millis - debounce_time) >= 20)        // On dinh it nhat 20ms
        {
            if (stable_button != raw_button)       // Trang thai on dinh vua thay doi
            {
                stable_button = raw_button;        // Cap nhat trang thai on dinh

                if (stable_button == 1)            // Chi xu ly khi vua nhan xuong
                {
                    if (DMA_UART1_IsBusy() == 0)   // Chi sua buffer khi DMA da ranh
                    {
                        button_count+=2;            // Tang so lan nhan

                        length = Create_Message(button_count); // Tao ban tin

                        DMA_UART1_Send(tx_buffer, length);      // Gui bang DMA
                    }
                }
            }
        }
    }
}
