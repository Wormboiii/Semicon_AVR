#include "../common/def.h"

#define LED_DDR DDRD
#define LED_PORT PORTD

typedef struct {
    volatile uint8_t *port;
    uint8_t pin_num;
}LED;

void led_init(LED *led);
void led_on(LED *led);
void led_off(LED *led);
void ledLeftShift(LED *led);