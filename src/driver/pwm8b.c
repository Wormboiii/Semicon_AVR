#include "pwm8b.h"

void regist_set() {         // 메인 함수에서 regist_set(); 로 불러오면 Fast PWM으로 TCCR0 세팅해줌
    regSet regset;
    regset.wgm0_fpwm = WGM00;
    regset.wgm1_fpwm = WGM01;
    regset.com_clr =COM01;
    TIMER_REG |= (1<<(regset.wgm0_fpwm)) | (1<<(regset.wgm1_fpwm)) | (1<<(regset.com_clr));
}

void prescaler_set(uint8_t a, uint8_t b, uint8_t c) {   // 메인 함수에서 prescaler_set(1, 0, 0); 처럼 불러오면 괄호 안에 숫자를 CS02, CS01, CS00에 넣어서 분주비 세팅. 
    TIMER_REG |= (a<<CS02) | (b<<CS01) | (c<<CS00);
}