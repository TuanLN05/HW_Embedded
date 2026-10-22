#ifndef LED_BUTTON_H
#define LED_BUTTON_H

#include "stm32f1xx.h"
#include <stdint.h>

/* Goi mot lan truoc cac task: PWM PA0..PA2 va nut pull-up PA5..PA7. */
void PWM_Init(void);
/* Dat duty 0..100% cho kenh 1..3; tham so ngoai pham vi bi bo qua. */
void PWM_SetDuty(uint8_t channel, uint8_t duty);

/* Goi tu mot task; ham cho 20 ms khi trang thai nut thay doi.
 * Tra bit 0/1/2 cho lan nhan moi PA5/PA6/PA7; tra 0 neu khong co.
 */
uint8_t Button_ReadPressed(void);

#endif
