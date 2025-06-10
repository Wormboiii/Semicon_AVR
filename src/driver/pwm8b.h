#ifndef __PWM8B_H__
#define __PWM8B_H__

#include "../common/def.h"

#define FPWM_OUT DDRB
#define TIMER_REG TCCR0
#define COUNT2TOP OCR0

typedef struct _regSet {
    volatile uint8_t wgm0_fpwm;
    volatile uint8_t wgm1_fpwm;
    volatile uint8_t com_clr;
}regSet;

void regist_set();
void prescaler_set(uint8_t a, uint8_t b, uint8_t c);


#endif /* __PWM8B_H__ */