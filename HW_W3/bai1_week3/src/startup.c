#include <stdint.h>

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;
int main(void);

void Default_Handler(void) { while (1); }
void NMI_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__((weak, alias("Default_Handler")));

void Reset_Handler(void)
{
    /* copy .data từ FLASH sang RAM */
    uint32_t *src = &_sidata, *dst = &_sdata;
    while (dst < &_edata) *dst++ = *src++;
    /* xoá .bss */
    for (dst = &_sbss; dst < &_ebss; ) *dst++ = 0;

    main();
    while (1);
}

__attribute__((section(".isr_vector"), used))
const uint32_t vector_table[] = {
    (uint32_t)&_estack,            /* 0: giá trị SP ban đầu */
    (uint32_t)Reset_Handler,       /* 1: Reset */
    (uint32_t)NMI_Handler,         /* 2 */
    (uint32_t)HardFault_Handler,   /* 3 */
    (uint32_t)MemManage_Handler,   /* 4 */
    (uint32_t)BusFault_Handler,    /* 5 */
    (uint32_t)UsageFault_Handler,  /* 6 */
    0, 0, 0, 0,                    /* 7-10: reserved */
    (uint32_t)SVC_Handler,         /* 11 */
    (uint32_t)DebugMon_Handler,    /* 12 */
    0,                             /* 13: reserved */
    (uint32_t)PendSV_Handler,      /* 14 */
    (uint32_t)SysTick_Handler,     /* 15 */
};
