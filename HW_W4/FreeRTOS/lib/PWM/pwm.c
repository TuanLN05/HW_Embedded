#include "pwm.h"
#include <math.h>

#define PWM_FREQUENCY_HZ 5000U
#define PWM_PI          3.14159265358979323846f

typedef struct
{
    volatile uint32_t *ccr;
    uint8_t percent;
    uint8_t enabled;
} pwm_channel_t;

static pwm_channel_t pwm_channels[4];

static bool pwm_get_channel(GPIO_TypeDef *gpio_port, uint8_t pin, pwm_channel_t **channel)
{
    if (gpio_port != GPIOA || pin > 3U || pwm_channels[pin].ccr == 0)
        return false;

    *channel = &pwm_channels[pin];
    return true;
}

static void pwm_apply_output(pwm_channel_t *channel)
{
    uint8_t output_percent = channel->enabled ? channel->percent : 0U;
    *channel->ccr = ((uint32_t)(TIM2->ARR + 1U) * output_percent) / 100U;
}

bool pwm_config(GPIO_TypeDef *gpio_port, uint8_t pin)
{
    uint32_t ccmr_shift;
    volatile uint32_t *ccmr;
    uint32_t ccer_enable;
    uint32_t apb1_prescaler;
    uint32_t timer_clock_hz;
    pwm_channel_t *channel;

    /* TIM2's default, non-remapped PWM pins on STM32F103C8 are PA0-PA3. */
    if (gpio_port != GPIOA || pin > 3U)
        return false;

    channel = &pwm_channels[pin];
    switch (pin)
    {
    case 0U:
        channel->ccr = &TIM2->CCR1;
        ccmr = &TIM2->CCMR1;
        ccmr_shift = 0U;
        ccer_enable = TIM_CCER_CC1E;
        break;
    case 1U:
        channel->ccr = &TIM2->CCR2;
        ccmr = &TIM2->CCMR1;
        ccmr_shift = 8U;
        ccer_enable = TIM_CCER_CC2E;
        break;
    case 2U:
        channel->ccr = &TIM2->CCR3;
        ccmr = &TIM2->CCMR2;
        ccmr_shift = 0U;
        ccer_enable = TIM_CCER_CC3E;
        break;
    default:
        channel->ccr = &TIM2->CCR4;
        ccmr = &TIM2->CCMR2;
        ccmr_shift = 8U;
        ccer_enable = TIM_CCER_CC4E;
        break;
    }

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= ~(0xFU << (4U * pin));
    GPIOA->CRL |= (0xBU << (4U * pin)); /* Alternate-function push-pull, 50 MHz. */

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    /* APB1 timers receive twice PCLK1 when the APB1 prescaler is not 1. */
    apb1_prescaler = (RCC->CFGR & RCC_CFGR_PPRE1) >> 8U;
    timer_clock_hz = SystemCoreClock;
    if (apb1_prescaler >= 4U)
        timer_clock_hz = (SystemCoreClock >> (apb1_prescaler - 3U)) * 2U;

    TIM2->PSC = 0U;
    TIM2->ARR = timer_clock_hz / PWM_FREQUENCY_HZ - 1U;
    channel->percent = 100U;
    channel->enabled = 0U;
    *channel->ccr = 0U;
    *ccmr &= ~(0xFFU << ccmr_shift);
    *ccmr |= (6U << (ccmr_shift + 4U)); /* PWM mode 1 */
    *ccmr |= (1U << (ccmr_shift + 3U)); /* Output compare preload. */
    TIM2->CCER |= ccer_enable;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;

    return true;
}

bool pwm_set_percent(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t percent)
{
    pwm_channel_t *channel;

    if (!pwm_get_channel(gpio_port, pin, &channel))
        return false;

    if (percent > 100U)
        percent = 100U;

    channel->percent = percent;
    pwm_apply_output(channel);
    return true;
}

bool pwm_set_duty(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t percent)
{
    return pwm_set_percent(gpio_port, pin, percent);
}

bool pwm_set_sine(GPIO_TypeDef *gpio_port, uint8_t pin,
                  uint32_t elapsed_ms, uint32_t period_ms)
{
    float phase;
    float duty_percent;

    if (period_ms == 0U)
        return false;

    phase = (float)(elapsed_ms % period_ms) / (float)period_ms;
    /* Shift sine by -pi/2: 0% -> 100% -> 0%, like the cosine example. */
    duty_percent = 50.0f * (1.0f + sinf(2.0f * PWM_PI * phase - PWM_PI / 2.0f));

    return pwm_set_percent(gpio_port, pin, (uint8_t)(duty_percent + 0.5f));
}

bool pwm_get_percent(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t *percent)
{
    pwm_channel_t *channel;

    if (percent == 0 || !pwm_get_channel(gpio_port, pin, &channel))
        return false;

    *percent = channel->percent;
    return true;
}

bool pwm_turn_on(GPIO_TypeDef *gpio_port, uint8_t pin)
{
    pwm_channel_t *channel;

    if (!pwm_get_channel(gpio_port, pin, &channel))
        return false;

    channel->enabled = 1U;
    pwm_apply_output(channel);
    return true;
}

bool pwm_turn_off(GPIO_TypeDef *gpio_port, uint8_t pin)
{
    pwm_channel_t *channel;

    if (!pwm_get_channel(gpio_port, pin, &channel))
        return false;

    channel->enabled = 0U;
    pwm_apply_output(channel);
    return true;
}

bool pwm_is_enabled(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t *enabled)
{
    pwm_channel_t *channel;

    if (enabled == 0 || !pwm_get_channel(gpio_port, pin, &channel))
        return false;

    *enabled = channel->enabled;
    return true;
}
