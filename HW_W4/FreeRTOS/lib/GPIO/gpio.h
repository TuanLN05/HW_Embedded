#ifndef GPIO_H
#define GPIO_H

#include "stm32f103xb.h"
#include "stdint.h"
#include "stdbool.h"


void GPIO_Config_Pin(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_Config_PinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, bool InoutCfg);
void GPIO_PinSet(GPIO_TypeDef *GPIOx, uint32_t Pin);
void GPIO_PinReset(GPIO_TypeDef *GPIOx, uint32_t Pin);
uint8_t GPIO_ReadOutPut_Databit(GPIO_TypeDef *GPIOx, uint32_t Pin);
uint8_t GPIO_ReadInPut_Databit(GPIO_TypeDef *GPIOx, uint32_t Pin);

#endif