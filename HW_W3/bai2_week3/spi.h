#ifndef SPI_H
#define SPI_H

#include "stm32f1xx.h"

void SPI1_Init(void);
void SPI1_SendByte(uint8_t data);

#endif
