#include "stm32f1xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "led_button.h"

typedef struct{
    uint8_t pin;
    uint8_t channel;
    QueueHandle_t queue;
} Led_t;
static Led_t led1 = {(1 << 0), 1};
static Led_t led2 = {(1 << 1), 2};
static Led_t led3 = {(1 << 2), 3};
static Led_t *leds[] = {&led1, &led2, &led3};
void LedTask(void *pvParameters){
    Led_t *led = (Led_t *)pvParameters;
    uint8_t duty;
    while (1) {
        if (xQueueReceive(led->queue, &duty, portMAX_DELAY) == pdPASS) {
            PWM_SetDuty(led->channel, duty);
        }
    }
}

void ButtonTask(void *pvParameters){
    uint8_t selected = 0;
    uint8_t duty[3] = {50, 50, 50};
    uint8_t blink_on = 0;
    TickType_t blink_start = 0;

    while (1) {
        /* Doc nut, cho them 20 ms neu can xac nhan trang thai moi.
         * Bit 0/1/2 tuong ung PA5/PA6/PA7, tra 0 neu chua co lan nhan moi.
         */
        uint8_t pressed = Button_ReadPressed();

        /* Bat PC13 khi bat ky nut nao co canh nhan da qua chong doi.
         * Nhan tiep khi LED dang sang se tinh lai 100 ms tu lan moi.
         */
        if (pressed != 0) {
            GPIOC->BRR = (1 << 13);
            blink_start = xTaskGetTickCount();
            blink_on = 1;
        }

        if (pressed & (1 << 0)) {
            /* PA5: chon LED1 -> LED2 -> LED3 -> LED1.
             * Chi doi LED duoc dieu chinh, khong tat cac LED con lai.
             */
            selected = (selected + 1) % 3;
        }

        /* 0x6 chi giu canh nhan cua PA6 va PA7.
         * Neu ca hai cung co canh nhan trong mau nay thi bo qua.
         * Neu PA5 cung co canh nhan, ap dung cho LED vua duoc chon.
         */
        if ((pressed & 0x6) == 2) {
            /* PA6: tang 10%. Duty bat dau 50 va chi doi theo buoc 10. */
            if (duty[selected] < 100) {
                duty[selected] += 10;
            }
            /* Queue dai 1: thay du lieu cu bang duty moi nhat.
             * Queue sao chep 1 byte, khong luu con tro vao mang duty.
             */
            xQueueOverwrite(leds[selected]->queue, &duty[selected]);
        } else if ((pressed & 0x6) == 4) {
            /* PA7: giam 10%, dung tai 0 de tranh tran uint8_t. */
            if (duty[selected] > 0) {
                duty[selected] -= 10;
            }
            xQueueOverwrite(leds[selected]->queue, &duty[selected]);
        }
        /* Tat PC13 sau 100 ms; viec kiem tra co the tre do cho debounce 20 ms.
         * Tru tick khong dau van dung khi bo dem tick tran.
         * Khong delay them 100 ms de tranh chan viec doc nut.
         */
        if (blink_on &&
            (TickType_t)(xTaskGetTickCount() - blink_start) >= pdMS_TO_TICKS(100)) {
            GPIOC->BSRR = (1 << 13);
            blink_on = 0;
        }
        /* Nhuong CPU cho task khac; doi 10 tick voi tick hien tai la 1 ms. */
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

int main(){
    PWM_Init();

    /* Moi LED co queue dai 1, moi phan tu la duty uint8_t.
     * Tao queue truoc task de task luon co queue hop le khi scheduler chay.
     */
    const char *names[] = {"LED1", "LED2", "LED3"};
    for (uint8_t i = 0; i < 3; i++) {
        leds[i]->queue = xQueueCreate(1, sizeof(uint8_t));
        /* Stack 128 word = 512 byte tren Cortex-M3; do uu tien 1.
         * leds[i] duoc truyen vao pvParameters de task biet LED can dieu khien.
         */
        BaseType_t result = xTaskCreate(LedTask, names[i], 128, leds[i], 1, NULL);
    }
    /* Task nut cung uu tien 1; khong can tham so nen truyen NULL. */
    BaseType_t result = xTaskCreate(ButtonTask, "Button", 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1){};
}
