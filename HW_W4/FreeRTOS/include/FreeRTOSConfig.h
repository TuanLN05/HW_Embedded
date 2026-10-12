#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f103xb.h"

#define configUSE_PREEMPTION                     1
#define configUSE_IDLE_HOOK                      0
#define configUSE_TICK_HOOK                      0

/* Use the actual clock updated before starting the scheduler. */
#define configCPU_CLOCK_HZ                      (SystemCoreClock)
#define configTICK_RATE_HZ                      1000
#define configUSE_16_BIT_TICKS                   0

#define configMAX_PRIORITIES                     5
#define configMINIMAL_STACK_SIZE                128
#define configMAX_TASK_NAME_LEN                 16

#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configSUPPORT_STATIC_ALLOCATION         0
#define configTOTAL_HEAP_SIZE                   (6 * 1024)

#define configUSE_TIMERS                         0
#define configUSE_CO_ROUTINES                    0

/* STM32F103 implements four NVIC priority bits. */
#define configKERNEL_INTERRUPT_PRIORITY         (15U << 4)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (5U << 4)

#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskDelayUntil                 1

/* Match the handler names in the CMSIS startup vector table. */
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler
#define xPortSysTickHandler                     SysTick_Handler

#define configASSERT(x)                         \
    do {                                       \
        if (!(x)) {                            \
            __disable_irq();                   \
            for (;;) {}                        \
        }                                      \
    } while (0)

#endif
