#ifndef __FND_H__
#define __FND_H__

#include "../common/def.h"

#define FND_DDR DDRF
#define FND_PORT PORTF

#define FND4_DDR            DDRA
#define FND4_PORT           PORTA
#define FND4_SELECT_DDR     DDRB
#define FND4_SELECT_PORT    PORTB

extern uint8_t Seg_num[10];
extern uint8_t Seg_alph[26];

void FND4_Init();
void FND4_Display(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3);

void seg_number_CA(int number); // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
void seg_number_CC(int number); // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
void seg_alph_CA(int alph);     // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
void seg_alph_CC(int alph);     // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.

#endif /* __FND_H__ */