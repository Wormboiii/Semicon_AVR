#include "button.h"

void button_init(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pin_num) {
    button->ddr = ddr;
    button->pin = pin;
    button->btn_pin = pin_num;
    button->prev_state = RELEASED;          // 초기화 상태로 아무것도 안누른 상태 
    *button->ddr &= ~(1<<button->btn_pin); // 버튼 핀을 입력으로 설정
    }

uint8_t button_get_state(BUTTON *button) {
    uint8_t cur_st = *button->pin & (1<<button->btn_pin); // 버튼의 상태를 읽어옴

    if((cur_st == PUSHED) && (button->prev_state == RELEASED)) {
        _delay_ms(50);
        button->prev_state = PUSHED;
        return ACT_PUSH;
    }
    else if((cur_st != PUSHED) && (button->prev_state == PUSHED)) {
        _delay_ms(50);
        button->prev_state = RELEASED;
        return ACT_RELEASE;
    }
    return NO_ACT;
}