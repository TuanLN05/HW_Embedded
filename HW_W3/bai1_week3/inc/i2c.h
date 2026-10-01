#pragma once
#include <stdint.h>

void i2c1_init(void);
int  i2c1_write(uint8_t addr7, const uint8_t *buf, uint32_t len); /* 0 = OK, -1 = lỗi */
