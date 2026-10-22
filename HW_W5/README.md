# HW_W5 - Bai1 va Bai2

Hai project PlatformIO nam tai `Bai1/Bai1` va `Bai2/Bai2`.
Board: STM32F103C8T6, SRAM 20 KiB, Flash 64 KiB, HSE 8 MHz.
`src/system_stm32f1xx.c` cau hinh CPU 72 MHz.

## Cac loi build da sua

- Bo sung FreeRTOS-Kernel V11.2.0 vao `lib` cua tung project, su dung ban
  kernel da co trong HW_W4. Moi bai co the build doc lap, khong can lay
  thu vien tu HW_W4. Kem port GCC ARM_CM3, heap_4 va giay phep MIT.
- Bo sung duong dan include cho kernel, port va `src/FreeRTOSConfig.h`.
- De trong `board_build.cmsis.system_file` de bo qua system file mac dinh
  cua CMSIS. Project da co `src/system_stm32f1xx.c`; chi dung mot ban de
  tranh trung `SystemInit`, `SystemCoreClock` va cac symbol lien quan.
- Dat Serial Monitor cua Bai2 thanh 115200 baud, khop UART1.

Toan bo cac file `.c` va `.h` goc trong `src` duoc giu nguyen.

## Build

Chay tu thu muc goc repository:

```powershell
pio run -d HW_W5/Bai1/Bai1
pio run -d HW_W5/Bai2/Bai2
```

Hoac mo thu muc chua `platformio.ini` cua tung bai trong VS Code va
chon PlatformIO: Build.

Firmware nam trong `.pio/build/genericSTM32F103C8/firmware.bin` cua tung bai.

Da build thanh cong bang PlatformIO ST STM32 20.0.0, GCC ARM 7.2.1:

| Project | RAM | Flash |
| --- | --- | --- |
| Bai1 | 8556 / 20480 byte | 5684 / 65536 byte |
| Bai2 | 8540 / 20480 byte | 5636 / 65536 byte |

Bai1 con hai canh bao `unused variable 'result'` trong `main`, khong ngan
build. Giu nguyen cac dong nay theo yeu cau khong sua ham chuc nang.
Chua nap va kiem thu tren board that.

## Dau noi de kiem thu

- Bai1: LED PWM tai PA0/PA1/PA2 (qua dien tro han dong); nut PA5 chon LED,
  PA6 tang duty, PA7 giam duty. Nut noi xuong GND, dung pull-up noi.
  Duty khoi tao 50%, thay doi 10% moi lan nhan; PC13 nhay khi nhan nut.
- Bai2: nut PA5 noi GND; PC13 nhay khi nhan. PA9 la UART1 TX, noi den RX
  cua USB-UART muc logic 3.3 V va noi chung GND. Serial: 115200, 8N1.
  Ket qua co dang `So lan nhan nut: 1`.

Tan so PWM, baud UART va tick RTOS phu thuoc clock 72 MHz, nen board can
co HSE 8 MHz dung voi cau hinh hien tai.
