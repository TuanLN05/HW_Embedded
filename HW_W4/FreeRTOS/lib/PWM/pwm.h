#ifndef PWM_H
#define PWM_H

#include "stm32f103xb.h"
#include <stdbool.h>
#include <stdint.h>

/* Supports STM32F103 TIM2 default-mapped pins PA0-PA3; returns false otherwise. */
bool pwm_config(GPIO_TypeDef *gpio_port, uint8_t pin);
bool pwm_set_duty(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t percent);
/* Call periodically on a configured, enabled channel; starts at 0% duty.
 * Returns false for a zero period or an unsupported/unconfigured pin. */
bool pwm_set_sine(GPIO_TypeDef *gpio_port, uint8_t pin,
                  uint32_t elapsed_ms, uint32_t period_ms);
bool pwm_set_percent(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t percent);
bool pwm_get_percent(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t *percent);
bool pwm_turn_on(GPIO_TypeDef *gpio_port, uint8_t pin);
bool pwm_turn_off(GPIO_TypeDef *gpio_port, uint8_t pin);
bool pwm_is_enabled(GPIO_TypeDef *gpio_port, uint8_t pin, uint8_t *enabled);

#endif
