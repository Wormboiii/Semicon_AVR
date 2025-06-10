#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../common/def.h"

#define BUTTON_DDR DDRG
#define BUTTON_PIN PING
#define BUTTON_SUB_DDR DDRE
#define BUTTON_SUB_PIN PINE

#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2
#define BUTTON_4 4
#define BUTTON_5 5

enum {PUSHED, RELEASED};
enum {NO_ACT, ACT_PUSH, ACT_RELEASE};

typedef struct _button {
    volatile uint8_t *ddr;  // 레지스터에 쓰기, 읽기 하는 값들은 volatile 붙여서 최적화 금지
    volatile uint8_t *pin;  // pin이라는 레지스터에서 값을 읽음
    uint8_t btn_pin;
    uint8_t prev_state;
    uint8_t btnEnabled;
    }BUTTON;

void button_init(BUTTON *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pin_num);
uint8_t button_get_state(BUTTON *button);

#endif /* __BUTTON_H__ */