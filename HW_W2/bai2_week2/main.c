#include "systik.h"
#include "setled.h"

int main(){
    Led_Init();
    SysTick_Init();
    while(1){}
}
