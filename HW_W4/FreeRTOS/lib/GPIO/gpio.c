#include "gpio.h"


/**
  * @brief  Cau hinh chan GPIO.
  * @param  GPIOx: Cong GPIO can cau hinh
  * @param  Pin: Chan GPIO can cau hinh
  * @retval None
  */
void GPIO_Config_Pin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    if(Pin > 15) return;

    if(GPIOx == GPIOA) RCC->APB2ENR |= 1 << 2;
    else if(GPIOx == GPIOB) RCC->APB2ENR |= 1 << 3;
    else if(GPIOx == GPIOC) RCC->APB2ENR |= 1 << 4;
    else if(GPIOx == GPIOD) RCC->APB2ENR |= 1 << 5;

    if(Pin <= 7)
    {
        GPIOx->CRL &= ~(0xF << (4 * Pin));
        GPIOx->CRL |=  (0x3 << (4 * Pin));   // Output push-pull, 50MHz
    }
    else
    {
        GPIOx->CRH &= ~(0xF << (4 * (Pin - 8)));
        GPIOx->CRH |=  (0x3 << (4 * (Pin - 8)));
    }
}
/**
  * @brief  Cau hinh che do vao/ra cho chan GPIO.
  * @param  GPIOx: Cong GPIO can cau hinh
  * @param  Pin: Chan GPIO can cau hinh
  * @param  InoutCfg:
  *         - true  : cau hinh chan o che do output
  *         - false : cau hinh chan o che do input
  * @retval None
  */
void GPIO_Config_PinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, bool InoutCfg)
{
    if(Pin > 15) return;

    if(GPIOx == GPIOA) RCC->APB2ENR |= 1 << 2;
    else if(GPIOx == GPIOB) RCC->APB2ENR |= 1 << 3;
    else if(GPIOx == GPIOC) RCC->APB2ENR |= 1 << 4;
    else if(GPIOx == GPIOD) RCC->APB2ENR |= 1 << 5;

    if(InoutCfg == true) // Output push-pull
    {
        if(Pin <= 7)
        {
            GPIOx->CRL &= ~(0xF << (4 * Pin));
            GPIOx->CRL |=  (0x3 << (4 * Pin));
        }
        else
        {
            GPIOx->CRH &= ~(0xF << (4 * (Pin - 8)));
            GPIOx->CRH |=  (0x3 << (4 * (Pin - 8)));
        }
    }
    else // Input floating
    {
        if(Pin <= 7)
        {
            GPIOx->CRL &= ~(0xF << (4 * Pin));
            GPIOx->CRL |=  (0x8 << (4 * Pin));
        }
        else
        {
            GPIOx->CRH &= ~(0xF << (4 * (Pin - 8)));
            GPIOx->CRH |=  (0x8 << (4 * (Pin - 8)));
        }
    }
}
/**
  * @brief  Dua chan GPIO len muc logic 1.
  * @param  GPIOx: Cong GPIO
  * @param  Pin: Chan GPIO can set
  * @retval None
  */
void GPIO_PinSet(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    if(Pin > 15) return;
    GPIOx->BSRR = 1 << Pin;
}

/**
  * @brief  Dua chan GPIO xuong muc logic 0.
  * @param  GPIOx: Cong GPIO
  * @param  Pin: Chan GPIO can reset
  * @retval None
  */
void GPIO_PinReset(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    if(Pin > 15) return;
    GPIOx->BSRR = 1 << (Pin + 16); // 16 -> 31 : reset
}
/**
  * @brief  Doc trang thai du lieu ngo ra cua chan GPIO.
  * @param  GPIOx: Cong GPIO
  * @param  Pin: Chan GPIO can doc
  * @retval Trang thai ngo ra cua chan GPIO (0 hoac 1)
  */
uint8_t GPIO_ReadOutPut_Databit(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    if((GPIOx->ODR & (1 << Pin)) != 0)
        return 0x01;
    else
        return 0x00;
}

/**
  * @brief  Doc trang thai du lieu ngo vao cua chan GPIO.
  * @param  GPIOx: Cong GPIO
  * @param  Pin: Chan GPIO can doc
  * @retval Trang thai ngo vao cua chan GPIO (0 hoac 1)
  */
uint8_t GPIO_ReadInPut_Databit(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    if((GPIOx->IDR & (1 << Pin)) != 0)
        return 0x01;
    else
        return 0x00;
}
