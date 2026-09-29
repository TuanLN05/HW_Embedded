#ifndef STM32F103XB_H
#define STM32F103XB_H

#include <stdint.h>

#define __IO volatile

typedef struct {
    __IO uint32_t CRL;
    __IO uint32_t CRH;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t BRR;
    __IO uint32_t LCKR;
} GPIO_TypeDef;

typedef struct {
    __IO uint32_t CR;
    __IO uint32_t CFGR;
    __IO uint32_t CIR;
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB1RSTR;
    __IO uint32_t AHBENR;
    __IO uint32_t APB2ENR;
    __IO uint32_t APB1ENR;
    __IO uint32_t BDCR;
    __IO uint32_t CSR;
    __IO uint32_t AHBRSTR;
    __IO uint32_t CFGR2;
} RCC_TypeDef;

typedef struct {
    __IO uint32_t ACR;
    __IO uint32_t KEYR;
    __IO uint32_t OPTKEYR;
    __IO uint32_t SR;
    __IO uint32_t CR;
    __IO uint32_t AR;
    __IO uint32_t RESERVED;
    __IO uint32_t OBR;
    __IO uint32_t WRPR;
} FLASH_TypeDef;

typedef struct {
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMCR;
    __IO uint32_t DIER;
    __IO uint32_t SR;
    __IO uint32_t EGR;
    __IO uint32_t CCMR1;
    __IO uint32_t CCMR2;
    __IO uint32_t CCER;
    __IO uint32_t CNT;
    __IO uint32_t PSC;
    __IO uint32_t ARR;
    __IO uint32_t RCR;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t CCR3;
    __IO uint32_t CCR4;
    __IO uint32_t BDTR;
    __IO uint32_t DCR;
    __IO uint32_t DMAR;
} TIM_TypeDef;

typedef struct {
    __IO uint32_t SR;
    __IO uint32_t DR;
    __IO uint32_t BRR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t CR3;
    __IO uint32_t GTPR;
} USART_TypeDef;

typedef struct {
    __IO uint32_t SR;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMPR1;
    __IO uint32_t SMPR2;
    __IO uint32_t JOFR1;
    __IO uint32_t JOFR2;
    __IO uint32_t JOFR3;
    __IO uint32_t JOFR4;
    __IO uint32_t HTR;
    __IO uint32_t LTR;
    __IO uint32_t SQR1;
    __IO uint32_t SQR2;
    __IO uint32_t SQR3;
    __IO uint32_t JSQR;
    __IO uint32_t JDR1;
    __IO uint32_t JDR2;
    __IO uint32_t JDR3;
    __IO uint32_t JDR4;
    __IO uint32_t DR;
} ADC_TypeDef;

typedef struct {
    __IO uint32_t ISR;
    __IO uint32_t IFCR;
} DMA_TypeDef;

typedef struct {
    __IO uint32_t CCR;
    __IO uint32_t CNDTR;
    __IO uint32_t CPAR;
    __IO uint32_t CMAR;
    uint32_t RESERVED;
} DMA_Channel_TypeDef;

typedef struct {
    __IO uint32_t CTRL;
    __IO uint32_t LOAD;
    __IO uint32_t VAL;
    __IO uint32_t CALIB;
} SysTick_Type;

#define GPIOA   ((GPIO_TypeDef *)0x40010800UL)
#define GPIOB   ((GPIO_TypeDef *)0x40010C00UL)
#define GPIOC   ((GPIO_TypeDef *)0x40011000UL)
#define ADC1    ((ADC_TypeDef *)0x40012400UL)
#define DMA1    ((DMA_TypeDef *)0x40020000UL)
#define DMA1_Channel1 ((DMA_Channel_TypeDef *)0x40020008UL)
#define DMA1_Channel2 ((DMA_Channel_TypeDef *)0x4002001CUL)
#define DMA1_Channel3 ((DMA_Channel_TypeDef *)0x40020030UL)
#define DMA1_Channel4 ((DMA_Channel_TypeDef *)0x40020044UL)
#define DMA1_Channel5 ((DMA_Channel_TypeDef *)0x40020058UL)
#define DMA1_Channel6 ((DMA_Channel_TypeDef *)0x4002006CUL)
#define DMA1_Channel7 ((DMA_Channel_TypeDef *)0x40020080UL)
#define RCC     ((RCC_TypeDef *)0x40021000UL)
#define FLASH   ((FLASH_TypeDef *)0x40022000UL)
#define TIM1    ((TIM_TypeDef *)0x40012C00UL)
#define TIM2    ((TIM_TypeDef *)0x40000000UL)
#define USART1  ((USART_TypeDef *)0x40013800UL)
#define SysTick ((SysTick_Type *)0xE000E010UL)

#define RCC_AHBENR_DMA1EN    (1UL << 0)
#define RCC_APB1ENR_TIM2EN   (1UL << 0)
#define RCC_APB2ENR_IOPAEN   (1UL << 2)
#define RCC_APB2ENR_IOPBEN   (1UL << 3)
#define RCC_APB2ENR_IOPCEN   (1UL << 4)
#define RCC_APB2ENR_ADC1EN   (1UL << 9)
#define RCC_APB2ENR_TIM1EN   (1UL << 11)
#define RCC_APB2ENR_USART1EN (1UL << 14)
#define GPIO_BSRR_BS10       (1UL << 10)

#define ADC_SR_EOC                (1UL << 1)
#define ADC_CR1_EOCIE             (1UL << 5)
#define ADC_CR2_ADON              (1UL << 0)
#define ADC_CR2_CAL               (1UL << 2)
#define ADC_CR2_RSTCAL            (1UL << 3)
#define ADC_CR2_DMA               (1UL << 8)
#define ADC_CR2_EXTSEL            (7UL << 17)
#define ADC_CR2_EXTSEL_TIM1_CC1   (0UL << 17)
#define ADC_CR2_EXTSEL_SWSTART    (7UL << 17)
#define ADC_CR2_EXTTRIG           (1UL << 20)
#define ADC_CR2_SWSTART           (1UL << 22)
#define ADC_CR2_TSVREFE           (1UL << 23)
#define ADC_SQR1_L                (15UL << 20)

#define TIM_CCMR1_OC1M       (7UL << 4)
#define TIM_CCMR1_OC1M_Pos   4U
#define TIM_CCMR1_OC1M_PWM1  (6UL << 4)
#define TIM_CCMR1_OC1PE      (1UL << 3)
#define TIM_CCER_CC1E        (1UL << 0)
#define TIM_BDTR_MOE         (1UL << 15)
#define TIM_CR1_CEN          (1UL << 0)
#define TIM_CR1_ARPE         (1UL << 7)
#define TIM_EGR_UG           (1UL << 0)

#define USART_SR_TXE         (1UL << 7)
#define USART_SR_RXNE        (1UL << 5)
#define USART_CR1_RE         (1UL << 2)
#define USART_CR1_TE         (1UL << 3)
#define USART_CR1_RXNEIE     (1UL << 5)
#define USART_CR1_UE         (1UL << 13)
#define USART_CR3_DMAR       (1UL << 6)
#define USART_CR3_DMAT       (1UL << 7)

#define DMA_ISR_GIF1         (1UL << 0)
#define DMA_ISR_TCIF1        (1UL << 1)
#define DMA_ISR_HTIF1        (1UL << 2)
#define DMA_ISR_TEIF1        (1UL << 3)
#define DMA_ISR_GIF2         (1UL << 4)
#define DMA_ISR_TCIF2        (1UL << 5)
#define DMA_ISR_HTIF2        (1UL << 6)
#define DMA_ISR_TEIF2        (1UL << 7)
#define DMA_ISR_GIF3         (1UL << 8)
#define DMA_ISR_TCIF3        (1UL << 9)
#define DMA_ISR_HTIF3        (1UL << 10)
#define DMA_ISR_TEIF3        (1UL << 11)
#define DMA_ISR_GIF4         (1UL << 12)
#define DMA_ISR_TCIF4        (1UL << 13)
#define DMA_ISR_HTIF4        (1UL << 14)
#define DMA_ISR_TEIF4        (1UL << 15)
#define DMA_ISR_GIF5         (1UL << 16)
#define DMA_ISR_TCIF5        (1UL << 17)
#define DMA_ISR_HTIF5        (1UL << 18)
#define DMA_ISR_TEIF5        (1UL << 19)
#define DMA_ISR_GIF6         (1UL << 20)
#define DMA_ISR_TCIF6        (1UL << 21)
#define DMA_ISR_HTIF6        (1UL << 22)
#define DMA_ISR_TEIF6        (1UL << 23)
#define DMA_ISR_GIF7         (1UL << 24)
#define DMA_ISR_TCIF7        (1UL << 25)
#define DMA_ISR_HTIF7        (1UL << 26)
#define DMA_ISR_TEIF7        (1UL << 27)

#define DMA_IFCR_CGIF1       (1UL << 0)
#define DMA_IFCR_CTCIF1      (1UL << 1)
#define DMA_IFCR_CHTIF1      (1UL << 2)
#define DMA_IFCR_CTEIF1      (1UL << 3)
#define DMA_IFCR_CGIF2       (1UL << 4)
#define DMA_IFCR_CTCIF2      (1UL << 5)
#define DMA_IFCR_CHTIF2      (1UL << 6)
#define DMA_IFCR_CTEIF2      (1UL << 7)
#define DMA_IFCR_CGIF3       (1UL << 8)
#define DMA_IFCR_CTCIF3      (1UL << 9)
#define DMA_IFCR_CHTIF3      (1UL << 10)
#define DMA_IFCR_CTEIF3      (1UL << 11)
#define DMA_IFCR_CGIF4       (1UL << 12)
#define DMA_IFCR_CTCIF4      (1UL << 13)
#define DMA_IFCR_CHTIF4      (1UL << 14)
#define DMA_IFCR_CTEIF4      (1UL << 15)
#define DMA_IFCR_CGIF5       (1UL << 16)
#define DMA_IFCR_CTCIF5      (1UL << 17)
#define DMA_IFCR_CHTIF5      (1UL << 18)
#define DMA_IFCR_CTEIF5      (1UL << 19)
#define DMA_IFCR_CGIF6       (1UL << 20)
#define DMA_IFCR_CTCIF6      (1UL << 21)
#define DMA_IFCR_CHTIF6      (1UL << 22)
#define DMA_IFCR_CTEIF6      (1UL << 23)
#define DMA_IFCR_CGIF7       (1UL << 24)
#define DMA_IFCR_CTCIF7      (1UL << 25)
#define DMA_IFCR_CHTIF7      (1UL << 26)
#define DMA_IFCR_CTEIF7      (1UL << 27)

#define DMA_CCR_EN           (1UL << 0)
#define DMA_CCR_TCIE         (1UL << 1)
#define DMA_CCR_HTIE         (1UL << 2)
#define DMA_CCR_TEIE         (1UL << 3)
#define DMA_CCR_DIR          (1UL << 4)
#define DMA_CCR_CIRC         (1UL << 5)
#define DMA_CCR_PINC         (1UL << 6)
#define DMA_CCR_MINC         (1UL << 7)
#define DMA_CCR_PSIZE_Pos    8U
#define DMA_CCR_PSIZE        (3UL << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_PSIZE_8BIT   (0UL << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_PSIZE_16BIT  (1UL << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_PSIZE_32BIT  (2UL << DMA_CCR_PSIZE_Pos)
#define DMA_CCR_MSIZE_Pos    10U
#define DMA_CCR_MSIZE        (3UL << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_MSIZE_8BIT   (0UL << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_MSIZE_16BIT  (1UL << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_MSIZE_32BIT  (2UL << DMA_CCR_MSIZE_Pos)
#define DMA_CCR_PL_Pos       12U
#define DMA_CCR_PL           (3UL << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_LOW       (0UL << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_MEDIUM    (1UL << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_HIGH      (2UL << DMA_CCR_PL_Pos)
#define DMA_CCR_PL_VERY_HIGH (3UL << DMA_CCR_PL_Pos)
#define DMA_CCR_MEM2MEM      (1UL << 14)

#define DMA_CNDTR_NDT        (0xFFFFUL)

#define RCC_CR_HSEON         (1UL << 16)
#define RCC_CR_HSERDY        (1UL << 17)
#define RCC_CR_PLLON         (1UL << 24)
#define RCC_CR_PLLRDY        (1UL << 25)
#define RCC_CFGR_SW          (3UL << 0)
#define RCC_CFGR_SWS         (3UL << 2)
#define RCC_CFGR_HPRE        (15UL << 4)
#define RCC_CFGR_PPRE1       (7UL << 8)
#define RCC_CFGR_PPRE2       (7UL << 11)
#define RCC_CFGR_ADCPRE      (3UL << 14)
#define RCC_CFGR_PLLSRC      (1UL << 16)
#define RCC_CFGR_PLLXTPRE    (1UL << 17)
#define RCC_CFGR_PLLMULL     (15UL << 18)
#define RCC_CFGR_HPRE_Pos    4U
#define RCC_CFGR_PLLMULL_Pos 18U
#define RCC_CFGR_HPRE_DIV1   (0UL << 4)
#define RCC_CFGR_PPRE1_DIV2  (4UL << 8)
#define RCC_CFGR_PPRE2_DIV1  (0UL << 11)
#define RCC_CFGR_ADCPRE_DIV6 (2UL << 14)
#define RCC_CFGR_PLLMULL9    (7UL << 18)
#define RCC_CFGR_SW_PLL      (2UL << 0)
#define RCC_CFGR_SWS_HSI     (0UL << 2)
#define RCC_CFGR_SWS_HSE     (1UL << 2)
#define RCC_CFGR_SWS_PLL     (2UL << 2)
#define FLASH_ACR_PRFTBE     (1UL << 4)
#define FLASH_ACR_LATENCY_2  (2UL << 0)

typedef enum {
    DMA1_Channel1_IRQn = 11,
    DMA1_Channel2_IRQn = 12,
    DMA1_Channel3_IRQn = 13,
    DMA1_Channel4_IRQn = 14,
    DMA1_Channel5_IRQn = 15,
    DMA1_Channel6_IRQn = 16,
    DMA1_Channel7_IRQn = 17,
    USART1_IRQn = 37
} IRQn_Type;

static inline void NVIC_EnableIRQ(IRQn_Type irqn)
{
    uint32_t irq_number = (uint32_t)irqn;
    uint32_t register_offset = (irq_number >> 5U) * sizeof(uint32_t);
    uint32_t bit_mask = 1UL << (irq_number & 31U);

    *(volatile uint32_t *)(0xE000E100UL + register_offset) = bit_mask;
}

static inline void NVIC_ClearPendingIRQ(IRQn_Type irqn)
{
    uint32_t irq_number = (uint32_t)irqn;
    uint32_t register_offset = (irq_number >> 5U) * sizeof(uint32_t);
    uint32_t bit_mask = 1UL << (irq_number & 31U);

    *(volatile uint32_t *)(0xE000E280UL + register_offset) = bit_mask;
}

extern uint32_t SystemCoreClock;

void SystemInit(void);
void SystemCoreClockUpdate(void);

#endif
