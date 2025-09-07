#include "app.h"


void app_init() {
    
}

void app_main() {
    FND_DDR = 0xff;            // DDRF 출력으로 설정(FND)
    FPWM_OUT |= (1 << PB4);    // PB4에 8비트 FPWM 출력
    FPWM16_OUT |= (1<<PB5);    // PB5에 16비트 FPWM 출력

    regist_set();   // 8비트 FPWM 세팅
    prescaler_set(1, 0, 0); // 프리스케일러 64분주

    all_regist_set();   //16비트 FPWM 세팅
    prescaler_set_16(0, 1, 1); //프리스케일러 64분주

    ICR1 = 4999;    // TOP값(주파수)
    
    BUTTON btn1;
    BUTTON btn2;
    BUTTON btn3;
    BUTTON btn4;

    button_init(&btn1, &BUTTON_DDR, &BUTTON_PIN, BUTTON_1); // 버튼 세팅
    button_init(&btn2, &BUTTON_DDR, &BUTTON_PIN, BUTTON_2);
    button_init(&btn3, &BUTTON_DDR, &BUTTON_PIN, BUTTON_3);
    button_init(&btn4, &BUTTON_SUB_DDR, &BUTTON_SUB_PIN, BUTTON_4);

    seg_number_CA(0);       // FND에 0 출력(초기값으로)

    uint8_t servoEnalbed = 0;   // 서보모터 상태(초기값 꺼짐)
    uint16_t servoPos = 370;    // 서보모터 초기 중앙정렬
    int8_t servoDirect = 5;      // 서보모터 증감값 초기 설정

    OCR1A = servoPos;           // 16비트 PWM OC레지스터에 듀티값 넣기(각도 조절하는 값 넣기)


    while (1) {
        if (button_get_state(&btn1) == RELEASED) {    // 첫번째 버튼 눌리면
            seg_number_CA(0);                         // FND에 0 출력
            OCR0 = 0;                                 // 8비트 PWM 듀티비 0%로 출력(꺼짐)
            servoEnalbed = 0;                         // 서보모터 정지(회전 OFF)
        }

        if (button_get_state(&btn2) == RELEASED) {    // 두번째 버튼 눌리면
            seg_number_CA(1);                         // FND에 1 출력(1단)
            OCR0 = 125;                               // 8비트 PWM 듀티비 대략 50%로 출력(1단)
        }

        if (button_get_state(&btn3) == RELEASED) {    // 세번째 버튼 눌리면
            seg_number_CA(2);                         // FND에 2 출력(2단)
            OCR0 = 204;                               // 8비트 PWM 듀티비 대략 80&로 출력(2단) 
        }

         if (button_get_state(&btn4) == RELEASED) {   // 네번쨰 버튼 눌리면
            servoEnalbed = !servoEnalbed;             // 서보모터 토글(껐다켰다)
        }

        if (servoEnalbed == 1) {            // 서보모터 상태가 1(켜짐)이면
            servoPos += servoDirect;         // 서보모터 듀티값을 증감값만큰 더해서 저장(초기값 370 + 5), 회전 시작

            if(servoPos >= 635) {           // 현재 서보모터 각도가 -90도를 찍었거나 넘었으면
                servoPos = 635;             // -90도로 설정해 준 다음
                servoDirect = -5;            // 증감값 초기(+5)에서 -5로 변경
            }
            else if (servoPos < 105) {      // 현재 서보모터 각도가 +90도를 넘었으면
                servoPos = 105;             // +90도로 설정해 준 다음
                servoDirect = 5;             // 증감값을 +5로 변경
            }
            OCR1A = servoPos;               //위 연산값을 16비트 PWM OC레지스터에 듀티값에 넣고
        }
        _delay_ms(10);                      // 부드러운 연산(회전)을 위해 딜레이 걸어줌 

    }   
}
