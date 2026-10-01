#include "stm32f103.h"
#include "i2c.h"

static int wait_flag(volatile uint32_t *reg, uint32_t mask)
{
    uint32_t t = 20000;
    while (!(*reg & mask)) {
        if (--t == 0) return -1;
    }
    return 0;
}

void i2c1_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    /* PB6 (SCL), PB7 (SDA): AF open-drain 50MHz = 0xF */
    GPIOB->CRL &= ~((0xFu << 24) | (0xFu << 28));
    GPIOB->CRL |=  ((0xFu << 24) | (0xFu << 28));

    I2C1->CR1 |= I2C_CR1_SWRST;      /* reset ngoại vi */
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2   = 8;                 /* PCLK1 = 8 MHz */
    I2C1->CCR   = 40;                /* 100kHz: 5us / 125ns = 40 */
    I2C1->TRISE = 9;                 /* 1000ns / 125ns + 1 */
    I2C1->CR1  |= I2C_CR1_PE;
}

int i2c1_write(uint8_t addr7, const uint8_t *buf, uint32_t len)
{
    I2C1->CR1 |= I2C_CR1_START;
    if (wait_flag(&I2C1->SR1, I2C_SR1_SB)) goto err;

    I2C1->DR = (uint32_t)(addr7 << 1);            /* bit0 = 0: ghi */
    if (wait_flag(&I2C1->SR1, I2C_SR1_ADDR | I2C_SR1_AF)) goto err;
    if (I2C1->SR1 & I2C_SR1_AF) goto err;         /* slave không ACK */
    (void)I2C1->SR1; (void)I2C1->SR2;             /* đọc SR1 rồi SR2 để xoá ADDR */

    for (uint32_t i = 0; i < len; i++) {
        if (wait_flag(&I2C1->SR1, I2C_SR1_TXE)) goto err;
        I2C1->DR = buf[i];
    }
    if (len && wait_flag(&I2C1->SR1, I2C_SR1_BTF)) goto err;

    I2C1->CR1 |= I2C_CR1_STOP;
    while (I2C1->CR1 & I2C_CR1_STOP);             /* chờ STOP hoàn tất */
    return 0;

err:
    I2C1->SR1 &= ~I2C_SR1_AF;
    I2C1->CR1 |= I2C_CR1_STOP;
    for (volatile int i = 0; i < 2000; i++);
    return -1;
}
