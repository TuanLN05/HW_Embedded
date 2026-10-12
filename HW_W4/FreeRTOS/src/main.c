#include "gpio.h"
#include "stm32f103xb.h"
#include "stdint.h"
#include "stdbool.h"
#include "pwm.h"
#include "app_tasks.h"
void delay(uint32_t time)
{
    while (time--)
    {
        SysTick->LOAD = 72000 - 1; // 1ms
        SysTick->VAL = 0;
        SysTick->CTRL = 5; // Enable SysTick
        while (!(SysTick->CTRL & 1 << 16))
            ; // Wait for COUNTFLAG
        time--;
    }
}
int main(void)
{
    SystemCoreClockUpdate();

#ifdef pwm_debug
    pwm_config(GPIOA, 0);
    pwm_config(GPIOA, 1);
    pwm_config(GPIOA, 2);
#endif

    GPIO_Config_Pin(GPIOA, 0);
    GPIO_Config_Pin(GPIOA, 1);
    GPIO_Config_Pin(GPIOA, 2);
    /* PA3/TIM2_CH4 drives the sine brightness effect. */
    bool sine_pwm_configured = pwm_config(GPIOA, 3);
    configASSERT(sine_pwm_configured);
    pwm_set_duty(GPIOA, 3, 0);
    pwm_turn_on(GPIOA, 3);
    xTaskCreate(vTask_0_1Hz, "Task 1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTask_1Hz, "Task 2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vTask_10Hz, "Task 3", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    BaseType_t sine_task_created = xTaskCreate(vTask_LedSine, "LED Sine",
                                               256, NULL, 1, NULL);
    configASSERT(sine_task_created == pdPASS);
    vTaskStartScheduler();
    while (1)
    {
#ifdef pwm_debug
        for (int8_t i = 0; i < 100; i++)
        {
            pwm_set_duty(GPIOA, 0, i);
            pwm_turn_on(GPIOA, 0);
            delay(50);
            pwm_set_duty(GPIOA, 1, i);
            pwm_turn_on(GPIOA, 1);
            delay(50);
            pwm_set_duty(GPIOA, 2, i);
            pwm_turn_on(GPIOA, 2);
            delay(50);
        }
#endif

    }

    return 0;
}
