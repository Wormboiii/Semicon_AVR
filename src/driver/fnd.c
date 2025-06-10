#include "fnd.h"

uint8_t Seg_num[] = {
        0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67
    };

uint8_t Seg_alph[] = {
    0x5f, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x3d, 0x76, 0x11, 0x0d, 0x75, 0x38, 0x55, 0x54, 0x5c, 0x73, 0x67, 0x50, 0x2d, 0x78, 0x1c, 0x2a, 0x6a, 0x14, 0x6e, 0x1b
};



void seg_number_CA(int number) {    // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
    FND_PORT = ~Seg_num[number];    // 함수를 호출 후 괄호 안에 0~9의 숫자를 넣으면 해당 숫자 FND에 출력.
}

void seg_number_CC(int number) {    // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
    FND_PORT = Seg_num[number];     // 함수를 호출 후 괄호 안에 0~9의 숫자를 넣으면 해당 숫자 FND에 출력.
}

void seg_alph_CA(int alph) {        // 애노드 공통, 이상하게 나오면 캐소드 공통 사용.
    FND_PORT = ~Seg_alph[alph];     // 함수를 호출 후 괄호 안에 숫자를 넣으면 0부터 순서대로 a,b,c... 알파벳이 나옴
}

void seg_alph_CC(int alph) {        // 캐소드 공통, 이상하게 나오면 애노드 공통 사용.
    FND_PORT = Seg_alph[alph];     // 함수를 호출 후 괄호 안에 숫자를 넣으면 0부터 순서대로 a,b,c... 알파벳이 나옴
}

// FND4 출력 설정 초기화 함수
void FND4_Init() {
    FND4_DDR = 0xff;        // PORTA 출력 설정, FND4 연결
    FND4_SELECT_DDR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);       // PORTB 0 ~ 3 출력 설정
    FND4_SELECT_PORT &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));   // PORTB 0 ~ 3 초기값 0
}

// FND4 출력 함수
// selectx 는 0 은 숫자, 1 은 영문, 2 는 초기화, x 왼쪽부터 0 ~ 3 자리
// numx 은 나타내려는 숫자나 영문 번호, x 왼쪽부터 0 ~ 3 자리
void FND4_Display(uint8_t select0, uint8_t num0, uint8_t select1, uint8_t num1,
    uint8_t select2, uint8_t num2, uint8_t select3, uint8_t num3) {
    for (uint8_t pos = 0; pos < 4; pos++) {
        switch (pos) {
        case 0:
        FND4_SELECT_PORT &= ~(1 << 0);
        FND4_SELECT_PORT |= (1 << 1) | (1 << 2) | (1 << 3);
        if (select0 == 0) {
            FND4_PORT = Seg_num[num0];
        }
        else if (select0 == 1) {
            FND4_PORT = Seg_alph[num0];
        }
        else if (select0 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 1:
        FND4_SELECT_PORT &= ~(1 << 1);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 2) | (1 << 3);
        if (select1 == 0) {
            FND4_PORT = Seg_num[num1];
        }
        else if (select1 == 1) {
            FND4_PORT = Seg_alph[num1];
        }
        else if (select1 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 2:
        FND4_SELECT_PORT &= ~(1 << 2);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 3);
        if (select2 == 0) {
            FND4_PORT = Seg_num[num2];
        }
        else if (select2 == 1) {
            FND4_PORT = Seg_alph[num2];
        }
        else if (select2 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;

        case 3:
        FND4_SELECT_PORT &= ~(1 << 3);
        FND4_SELECT_PORT |= (1 << 0) | (1 << 1) | (1 << 2);
        if (select3 == 0) {
            FND4_PORT = Seg_num[num3];
        }
        else if (select3 == 1) {
            FND4_PORT = Seg_alph[num3];
        }
        else if (select3 == 2) {
            FND4_PORT = 0x00;
        }
        _delay_ms(1);                       // 1ms 대기
        break;
        }
    }
}