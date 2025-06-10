#ifndef __PWM16_H__
#define __PWM16_H__

#include "../common/def.h"  

#define FPWM16_OUT DDRB
#define TIMER_REG_A TCCR1A
#define TIMER_REG_B TCCR1B

typedef struct _allRegset {
    volatile uint8_t wgm1_16fpwm;
    volatile uint8_t wgm2_16fpwm;
    volatile uint8_t wgm3_16fpwm;
    volatile uint8_t com_clr_16b;
}allRegset;

void all_regist_set();
void prescaler_set_16(uint8_t a, uint8_t b, uint8_t c);

#endif /* __PWM16_H__ */
