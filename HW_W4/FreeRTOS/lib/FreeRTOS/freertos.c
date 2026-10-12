#include "app_tasks.h"
#include "pwm.h"
#include "gpio.h"

void vTask_LedSine(void *pvParameters)
{
    const TickType_t period_ticks = pdMS_TO_TICKS(4000U);
    const TickType_t update_ticks = pdMS_TO_TICKS(10U);
    TickType_t previous_tick = xTaskGetTickCount();
    TickType_t last_wake_tick = previous_tick;
    TickType_t phase_ticks = 0;

    (void)pvParameters;
    for (;;)
    {
        TickType_t now = xTaskGetTickCount();
        /* Accumulate elapsed time modulo the period, including tick wrap. */
        phase_ticks = (phase_ticks + (now - previous_tick) % period_ticks) % period_ticks;
        previous_tick = now;
        pwm_set_sine(GPIOA, 3, phase_ticks * portTICK_PERIOD_MS, 4000U);
        xTaskDelayUntil(&last_wake_tick, update_ticks);
    }
}

void vTask_0_1Hz(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        GPIO_PinSet(GPIOA, 0);
        vTaskDelay(pdMS_TO_TICKS(5000));
        GPIO_PinReset(GPIOA, 0);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void vTask_1Hz(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        GPIO_PinSet(GPIOA, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIO_PinReset(GPIOA, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void vTask_10Hz(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        GPIO_PinSet(GPIOA, 2);
        vTaskDelay(pdMS_TO_TICKS(50));
        GPIO_PinReset(GPIOA, 2);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
