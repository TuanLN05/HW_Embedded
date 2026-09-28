- Build: make clean + make
- flash: St-link: make flash-stlink
         Daplink: make flash-daplink
- Mo monitor: picocom -b _baurate_ --echo /dev/ttyACM0
    - "ON!" : Led on
    - "OFF!": Led off
    - "PWM: x%!": tang giam do sang cho led
    - "Status!" : doc trang thai cua led


- Loi ko vao duoc ngat: kiem tra dia chi ngat (dia chi co dinh NVIC co dinh sai bank)