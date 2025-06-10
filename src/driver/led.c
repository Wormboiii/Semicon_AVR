#include "led.h"

void led_init(LED *led) {
    *(led->port - 1) |= (1 << led->pin_num); // DDR 레지스터는 PORT 레지스터보다 1 낮으므로 -1을 이용해 DDR로 접근
}


void led_on(LED *led) {
    *(led->port) |= (1 << led->pin_num); // 내가 원하는 자리의 핀을 HIGH로 설정
}


void led_off(LED *led) {
    *(led->port) &= ~(1 << led->pin_num); // 내가 원하는 자리의 핀을 LOW로 설정
}

void ledLeftShift(LED *led) {
    *(led->port) = (led->pin_num << 1);
}
