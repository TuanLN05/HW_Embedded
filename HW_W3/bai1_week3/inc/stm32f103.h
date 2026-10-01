#pragma once
#include <stdint.h>

/* ---- RCC (0x40021000) ---- */
typedef struct {
    volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR,
                      AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
} RCC_t;
static volatile RCC_t *const RCC = (volatile RCC_t *)0x40021000UL;

enum {
    RCC_APB2ENR_IOPBEN = 1u << 3,
    RCC_APB2ENR_IOPCEN = 1u << 4,
    RCC_APB1ENR_I2C1EN = 1u << 21
};

/* ---- GPIO ---- */
typedef struct {
    volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} GPIO_t;
static volatile GPIO_t *const GPIOB = (volatile GPIO_t *)0x40010C00UL;
static volatile GPIO_t *const GPIOC = (volatile GPIO_t *)0x40011000UL;

/* ---- I2C1 (0x40005400) ---- */
typedef struct {
    volatile uint32_t CR1, CR2, OAR1, OAR2, DR, SR1, SR2, CCR, TRISE;
} I2C_t;
static volatile I2C_t *const I2C1 = (volatile I2C_t *)0x40005400UL;

enum {
    I2C_CR1_PE    = 1u << 0,
    I2C_CR1_START = 1u << 8,
    I2C_CR1_STOP  = 1u << 9,
    I2C_CR1_SWRST = 1u << 15,

    I2C_SR1_SB    = 1u << 0,
    I2C_SR1_ADDR  = 1u << 1,
    I2C_SR1_BTF   = 1u << 2,
    I2C_SR1_TXE   = 1u << 7,
    I2C_SR1_AF    = 1u << 10
};
