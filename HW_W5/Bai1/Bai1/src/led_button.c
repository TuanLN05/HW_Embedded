#include "led_button.h"
#include "FreeRTOS.h"
#include "task.h"
void PWM_Init(void){
    /* Bat clock GPIOA va TIM2. */
    RCC->APB2ENR |= (1 << 2);
    RCC->APB1ENR |= (1 << 0);

    /* Cau hinh PC13 output push-pull 2 MHz, ban dau tat LED. */
    RCC->APB2ENR |= (1 << 4);
    GPIOC->BSRR = (1 << 13);
    GPIOC->CRH &= ~(0xF << 20);
    GPIOC->CRH |= (0x2 << 20);

    /* PA0, PA1, PA2: ngo ra PWM TIM2_CH1, CH2, CH3, AF push-pull 2 MHz. */
    GPIOA->CRL &= ~((0xF << 0) | (0xF << 4) | (0xF << 8));
    GPIOA->CRL |= (0xA << 0) | (0xA << 4) | (0xA << 8);

    /* PA5/PA6/PA7: nut chuyen/tang/giam, input pull-up, nhan muc 0. */
    GPIOA->BSRR = (1 << 5) | (1 << 6) | (1 << 7);
    GPIOA->CRL &= ~((0xFU << 20) | (0xFU << 24) | (0xFU << 28));
    GPIOA->CRL |= (0x8U << 20) | (0x8U << 24) | (0x8U << 28);

    /* Tam dung timer va ngo ra, chon dem len va preload ARR. */
    TIM2->CR1 = (1 << 7);
    TIM2->CCER = 0;

    /* Clock TIM2 72 MHz: PWM 1 kHz, duty ban dau 50% cho 3 kenh. */
    TIM2->PSC = 72 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->CCR1 = 500;
    TIM2->CCR2 = 500;
    TIM2->CCR3 = 500;

    /* Chon PWM mode 1 va preload CCR cho 3 kenh. */
    TIM2->CCMR1 = (6 << 4) | (1 << 3) | (6 << 12) | (1 << 11);
    TIM2->CCMR2 = (6 << 4) | (1 << 3);

    /* Nap gia tri, xoa co update, bat 3 kenh va timer. */
    TIM2->EGR = (1 << 0);
    TIM2->SR = 0;
    TIM2->CCER = (1 << 0) | (1 << 4) | (1 << 8);
    TIM2->CR1 |= (1 << 0);
}
void PWM_SetDuty(uint8_t channel, uint8_t duty){
    /* Bo qua kenh ngoai 1..3 hoac duty ngoai 0..100%. */
    if (channel < 1 || channel > 3 || duty > 100) {
        return;
    }

    /* Tinh CCR tu duty va so nhip moi chu ky. */
    uint32_t compare = (TIM2->ARR + 1) * duty / 100;

    /* Cap nhat duty kenh duoc chon tai su kien update tiep theo. */
    if (channel == 1) {
        TIM2->CCR1 = compare;
    } else if (channel == 2) {
        TIM2->CCR2 = compare;
    } else {
        TIM2->CCR3 = compare;
    }
}
/* Goi tu mot task; cho 20 ms khi trang thai nut thay doi. */
uint8_t Button_ReadPressed(void){
    /* Luu trang thai da xac nhan, giu nut khong lap. */
    static uint8_t stable = 0;

    /* Doc PA5..PA7 vao bit 0..2, quy uoc nhan la 1. */
    uint8_t buttons = (~GPIOA->IDR >> 5) & 0x7;

    /* Doc lai mot lan sau 20 ms; hai mau giong nhau thi chap nhan. */
    if (buttons != stable) {
        vTaskDelay(pdMS_TO_TICKS(20));
        if (buttons == ((~GPIOA->IDR >> 5) & 0x7)) {
            /* Cap nhat ca nhan va tha, chi tra cac nut moi nhan. */
            uint8_t pressed = buttons & ~stable;
            stable = buttons;
            return pressed;
        }
    }

    return 0;
}


