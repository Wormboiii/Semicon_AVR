#include "pwm16b.h"

void all_regist_set() {         // TCCR1A, TCCR1B에 COM, WGM 등을 설정해서 16비트 fast pwm으로 사용하게 설정하는 함수.
    allRegset allregset;        // 메인에서 불러올 때 all_regist_set(); 이렇게 쓰면 됨
    allregset.wgm1_16fpwm = WGM11;
    allregset.wgm2_16fpwm = WGM12;
    allregset.wgm3_16fpwm = WGM13;
    allregset.com_clr_16b = COM1A1;
    TIMER_REG_A |= (1<<(allregset.wgm1_16fpwm)) | (1<<(allregset.com_clr_16b));
    TIMER_REG_B |= (1<<(allregset.wgm2_16fpwm)) | (1<<(allregset.wgm3_16fpwm));
}

void prescaler_set_16(uint8_t a, uint8_t b, uint8_t c) {   // 프리스케일러를 설정하는 함수. 괄호 내에 CS12, CS11, CS10 순서로 입력. 0 or 1만 입력하기!!!!
    TIMER_REG_B |= (a<<CS12) | (b<<CS11) | (c<<CS10);
}