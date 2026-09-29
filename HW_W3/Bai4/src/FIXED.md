# Tom tat sua loi ADC

## `Inc/stm32f103xb.h`

- Them `ADC_TypeDef` theo dung thu tu thanh ghi cua ADC tren STM32F103.
- Them dia chi ngoai vi `ADC1`, `GPIOB` va `GPIOC`.
- Them cac bit bat clock cho ADC1, GPIOB va GPIOC.
- Them cac bit dieu khien ADC dung cho bat ADC, hieu chuan, software trigger,
  co EOC va kenh nhiet do/Vref noi.
- Them cau hinh ADC prescaler chia 6. Voi PCLK2 = 72 MHz, ADCCLK con 12 MHz,
  nam trong gioi han toi da 14 MHz cua STM32F103.

## `Inc/ADC/adc.h`

- Chuan hoa include guard thanh `ADC_H`.
- Giu API `uint16_t adc1_read(void)` de phu hop voi ten ham chi doc ADC1.

## `Inc/ADC/adc.c`

- Dong bo dinh nghia `adc1_read()` voi khai bao trong header; ham dung truc tiep
  `ADC1` thay vi nhan mot tham so `ADC_TypeDef *`.
- Kiem tra channel hop le trong khoang 0..17.
- Cau hinh chan analog cho cac kenh ngoai:
  - Channel 0..7: PA0..PA7.
  - Channel 8..9: PB0..PB1.
  - Channel 10..15: PC0..PC5.
- Bat `TSVREFE` khi dung channel 16 hoac 17.
- Cau hinh mot regular conversion va software trigger bang cac macro co ten.
- Bo ngat EOC vi chuong trinh dang doc ADC theo polling.
- Thay cac vong delay rong bang delay co bien `volatile`, tranh bi `-O2` xoa.
- Reset calibration va calibration theo dung thu tu sau khi bat ADC.
- Doc ket qua sau khi cho co `EOC`.

## `src/main.c`

- Doi loi goi `adc1_read(ADC1)` thanh `adc1_read()` cho dung prototype.
- Them `(void)adc_value` de khong phat sinh canh bao bien chua duoc su dung.

## Kiem tra

- `adc.c` va `main.c` da qua kiem tra cu phap bang `arm-none-eabi-gcc` voi
  `-Wall -Wextra`, khong con loi hoac canh bao ADC.
- Khi chay `make all`, `main.c` va `adc.c` deu bien dich thanh cong. Build toan bo
  dung tai `Inc/UART/uart.c` vi khong tim thay `pwm.h`. Day la loi cua module
  UART/PWM, khong phai loi ADC, nen khong duoc thay doi trong lan sua nay.



// config 
- PA0 PWM -> led
- PB0 - ADC1 - channe_8
- PA9 - TX - USART1
- PA10 - RX - USART1
- TIMER 1 or 8