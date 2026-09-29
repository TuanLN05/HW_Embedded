#include "dma.h"
#include "pwm.h"
#include "uart.h"

volatile uint16_t dma_adc_buffer[DMA_ADC_BUFFER_SIZE];

static void dma_uart_write_u16(uint16_t value)
{
    char digits[5];
    uint8_t length = 0U;

    do
    {
        digits[length] = (char)('0' + (value % 10U));
        length++;
        value /= 10U;
    } while (value != 0U);

    while (length > 0U)
    {
        length--;
        uartWrite((uint8_t)digits[length]);
    }

    uartWrite((uint8_t)'\n');
    uartWrite((uint8_t)'\r');
}

static void dma_uart_write_buffer(uint32_t first, uint32_t count)
{
    uint32_t index;

    for (index = first; index < (first + count); index++)
        dma_uart_write_u16(dma_adc_buffer[index]);
}

static void dma_update_led(uint32_t first, uint32_t count)
{
    uint32_t index;
    uint32_t sum = 0U;
    uint32_t average;
    uint8_t duty_percent;

    for (index = first; index < (first + count); index++)
        sum += dma_adc_buffer[index];

    average = sum / count;
    duty_percent = (uint8_t)((average * 100U + 2047U) / 4095U);
    pwm_set_percent(duty_percent);
}

void dma_adc(void)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* A DMA channel must be disabled while it is being configured. */
    DMA1_Channel1->CCR &= ~DMA_CCR_EN;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)dma_adc_buffer;
    DMA1_Channel1->CNDTR = DMA_ADC_BUFFER_SIZE;

    DMA1_Channel1->CCR = DMA_CCR_MINC |
                         DMA_CCR_PSIZE_16BIT |
                         DMA_CCR_MSIZE_16BIT |
                         DMA_CCR_CIRC |
                         DMA_CCR_HTIE |
                         DMA_CCR_TCIE;

    DMA1->IFCR = DMA_IFCR_CGIF1;
    NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    ADC1->CR2 |= ADC_CR2_DMA;
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}

void DMA1_Channel1_IRQHandler(void)
{
    uint32_t status = DMA1->ISR;

    if ((status & DMA_ISR_HTIF1) != 0U)
    {
        DMA1->IFCR = DMA_IFCR_CHTIF1;

        /* DMA is filling [50..99], so [0..49] is safe to transmit. */
        dma_update_led(0U, DMA_ADC_HALF_SIZE);
        dma_uart_write_buffer(0U, DMA_ADC_HALF_SIZE);
    }

    if ((status & DMA_ISR_TCIF1) != 0U)
    {
        DMA1->IFCR = DMA_IFCR_CTCIF1;

        /* DMA has wrapped to [0..49], so [50..99] is safe. */
        dma_update_led(DMA_ADC_HALF_SIZE, DMA_ADC_HALF_SIZE);
        dma_uart_write_buffer(DMA_ADC_HALF_SIZE, DMA_ADC_HALF_SIZE);
    }
}
