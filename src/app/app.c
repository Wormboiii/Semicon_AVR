#include "app.h"

/*
void app_init() {
    //아직 사용 x
}

void app_main() {
    LED_DDR = 0xff;
    BUTTON btn_on;  // 버튼 관련 변수 선언
    BUTTON btn_off;
    BUTTON btn_toggle;

    button_init(&btn_on, &BUTTON_DDR, &BUTTON_PIN, BUTTON_ON);
    button_init(&btn_off, &BUTTON_DDR, &BUTTON_PIN, BUTTON_OFF);
    button_init(&btn_toggle, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE);

    while(1) {
        if(button_get_state(&btn_on) == RELEASED) {
            LED_PORT = 0xff;
        }
        if(button_get_state(&btn_off) == RELEASED) {
            LED_PORT = 0x00;
        }
        if(button_get_state(&btn_toggle) == RELEASED) {
            LED_PORT ^= 0xff;
        }
    }
}
*/

/*
void app_init() {

}

ISR(INT4_vect) {
    LED_PORT = 0xff;
}

ISR(INT5_vect) {
    LED_PORT = 0x00;
}

void app_main() {
    sei();  // 전역 인터럽트 set

    // EICRB = 0x0E;       // INT4 하강엣지, INT5 상승엣지
    EICRB |= (1 << ISC51) | (1 << ISC50) | (1 << ISC41);

    // EIMSK = 0x30;       // INT4, INT5 Interrupt Enable
    EIMSK |= (1 << INT5) | (1<<INT4);

    DDRD = 0xff;        // D포트출력

    while(1) {

    }
}

*/

/*
void app_init() { 

}


void app_main() {
    DDRB = 0xff;    // pb4를 통한 주파수 출력을 위해 B포트 모두 출력으로 설정
    // TCCR0 = 0x1C;   // 레지스터 세팅(CTC모드, 토글모드, 분주비 64)
    TCCR0 |= (1<<WGM01) | (1<<COM00) | (1<<CS02) | (1<<CS00);

    OCR0 = 249;


    while(1) {
        while((TIFR & 0x02) == 0) {

        }
    TIFR = 0x02;
    OCR0 = 249;
    }
}
*/

/*
void app_init() { 

}


void app_main() {
    DDRD = 0xff;    // pb4를 통한 주파수 출력을 위해 B포트 모두 출력으로 설정
    PORTD = 0;
    TCCR0 |= (1<<CS00) | (1<<CS02); // (노말모드, 토글, 분주비 128)
    TCNT0 = 131;

    while(1) {
        while((TIFR & 0x01) == 0) {

        }
    PORTD = ~PORTD;
    TCNT0 = 131;
    TIFR = 0x01;
    }
}
*/

/*
void app_init() { 

}


void app_main() {
    DDRB |= (1<<PB4);    // pb4만 출력으로 설정
    TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS02);  // pwm모드
    OCR0 = 80; // 듀티사이클 100%
    while(1) {

    }
}
*/


/*
void app_init() { 

}


void app_main() {
    DDRB |= (1<<PB5);    // pb5만 출력으로 설정
    TCCR1A |= (1<<COM1A1) | (1<<WGM11); // 16비트 fast pwm 설정, 64분주 50hz
    TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);

    ICR1 = 4999;    // TOP값(주파수)
    //  OCR1A = 2500;   

    while(1) {
        OCR1A = 140; // -90도
        _delay_ms(1000);
        OCR1A = 630;    // +90도
        _delay_ms(1000);
    }
}
*/


/*
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
*/


void app_init() {

}

void app_main() {
    FND_DDR = 0xff;             // PORTF 출력 설정, FND 연결
    FND4_Init();                // PORTA, PORTB 0 ~ 3 초기화
    LED_DDR = 0xff;             // PORTD 출력 설정, LED 연결
    
    FPWM_OUT |= (1 << PB4) | (1 << PB5);     // PB4, PB5 port 출력
    
    // PORTG 0,1,2 입력 설정
    BUTTON_DDR |= ((1 << PG0) | (1 << PG1) | (1 << PG2));
    BUTTON_SUB_DDR |= (1<< PE4); 

    regist_set();               // 8-bit, Fast PWM, Clear
    prescaler_set(1, 0, 0);     // CS02, CS01, CS00 값 입력, 100 -> 62분주

    all_regist_set();           // 16-bit, Fast PWM, 64 분주, 50Hz
    prescaler_set_16(0, 1, 1);  // CS02, CS01, CS00 값 입력, 011 -> 62분주
    
    // Button 1 ~ 4 의 구조체 변수 선언
    // Button 의 위치 등과 btnEnabled 이라는 상태 변수 포함
    BUTTON btn1;
    BUTTON btn2;
    BUTTON btn3;
    BUTTON btn4;

    // Button 1 ~ 4 의 변수 초기화
    button_init(&btn1, &BUTTON_DDR, &BUTTON_PIN, BUTTON_1);
    button_init(&btn2, &BUTTON_DDR, &BUTTON_PIN, BUTTON_2);
    button_init(&btn3, &BUTTON_DDR, &BUTTON_PIN, BUTTON_3);
    button_init(&btn4, &BUTTON_SUB_DDR, &BUTTON_SUB_PIN, BUTTON_4);
    btn1.btnEnabled = 1;        // Button 1 상태는 초기값을 On 을 주어 STOP 상태로 시작
    uint8_t btnPrev = 1;        // Button 4 Spin 을 Off 했을 때 이전 버튼 상태를 기억해서 표현하기 위한 변수

    seg_number_CA(0);               // FND 초기값 0 출력
    
    int8_t servoDiret = 1;          // servo 의 이동 방향
    uint16_t servoPos = 370;        // servo 의 초기 위치
    uint8_t servoEnabled = 0;       // servo 의 작동 상태 기억, Fan 회전과 별도로 동작하게 하려고 별도 변수 지정
    
    OCR1A = servoPos;               // servo 의 초기 위치 적용

    uint8_t led_index = 0;          // LED 출력 위치
    // uint8_t led_direction = 1;
    uint8_t led_delay = 0;          // 함수가 아닌 자체적으로 delay 를 주기 위한 변수
    uint8_t led_delayLow = 20;      // Low 일때 delay 값, 50 ms * led_delayLow
    uint8_t led_delayHigh = 5;      // Low 일때 delay 값, 50 ms * led_delayHigh

    uint16_t pot_val;                // 가변저항 값을 저장할 변수 지정
    uint16_t prev_val = 0;


    init_ADC0();                     // ADC 기능 켜는 함수


    ICR1 = 4999;        // TOP 값, 50Hz

    while (1) {


        ADC_convert();
            pot_val = ADC;

            // if ( pot_val < 200) {
            //     COUNT2TOP = 140;
            // }
            // else if( 250 < pot_val && pot_val < 400) {
            //     COUNT2TOP = 160;
            // }
            // else if( 450 < pot_val && pot_val< 600) {
            //     COUNT2TOP = 180;
            // }
            // else if( 650 < pot_val && pot_val< 800) {
            //     COUNT2TOP = 200;
            // }
            // else if( 850 < pot_val) {
            //     COUNT2TOP = 220;
            // }


        // Button 1 이 눌리면 Button 1 상태 On, 나머지 버튼과 Servo Off, 이전 버튼 상태는 1 기억
        if (button_get_state(&btn1) == RELEASED) {
            btn1.btnEnabled = 1;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            servoEnabled = 0;
            btnPrev = 1;
        }
        
        // Button 1 이 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn1.btnEnabled == 1) {
            seg_number_CA(0);       // FND 0 출력

            // COUNT2TOP = 0;          // FAN 작동 안함
            if ( pot_val < 200) {
                COUNT2TOP = 140;
            }
            else if( 250 < pot_val && pot_val < 400) {
                COUNT2TOP = 160;
            }
            else if( 450 < pot_val && pot_val< 600) {
                COUNT2TOP = 180;
            }
            else if( 650 < pot_val && pot_val< 800) {
                COUNT2TOP = 200;
            }
            else if( 850 < pot_val) {
                COUNT2TOP = 220;
            }

            FND4_Display(1, 18, 1, 19, 1, 14, 1, 15);   // FND4 STOP 출력

            LED_PORT = 0x00;        // LED 출력 안함
        }

        // Button 2 눌리면 Button 2 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 2 기억
        if (button_get_state(&btn2) == RELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 1;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 0;
            btnPrev = 2;
        }

        // Button 2 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn2.btnEnabled == 1) {
            seg_number_CA(1);       // FND 1 출력

            

            FND4_Display(1, 11, 1, 14, 1, 22, 2, 0);   // FND4 LOW 출력

            // LED 를 index 위치에 출력, delay 변수에 따라 index 변경 시간 조절
            LED_PORT = (1 << led_index);
            if (led_delay >= led_delayLow) {
                led_index++;
                led_delay = 0;
            }
            led_delay++;
            if (led_index >= 8) {
                led_index = 0;      // LED 가 끝에 도달하면 다시 처음으로 index 변경
            }
        }

        // Button 3 눌리면 Button 3 상태 On, 나머지 버튼 Off, 이전 버튼 상태는 3 기억
        if (button_get_state(&btn3) == RELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 1;
            btn4.btnEnabled = 0;
            btnPrev = 3;
        }

        // Button 3 눌린 상태라면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn3.btnEnabled == 1) {
            seg_number_CA(2);       // FND 2 출력

            COUNT2TOP = 204;        // FAN 80%

            FND4_Display(1, 7, 1, 8, 1, 6, 1, 7);   // FND4 HIGH 출력

            // LED 를 index 위치에 출력, delay 변수에 따라 index 변경 시간 조절
            LED_PORT = (1 << led_index);
            if (led_delay >= led_delayHigh) {
                led_index++;
                led_delay = 0;
            }
            led_delay++;
            if (led_index >= 8) {
                led_index = 0;      // LED 가 끝에 도달하면 다시 처음으로 index 변경
            }
        }

        if (button_get_state(&btn4) == RELEASED) {
            btn1.btnEnabled = 0;
            btn2.btnEnabled = 0;
            btn3.btnEnabled = 0;
            btn4.btnEnabled = 1;
            servoEnabled = !servoEnabled;
        }

        // Button 4 눌린 상태 + servo 작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (btn4.btnEnabled == 1 && servoEnabled == 1) {
            FND4_Display(1, 18, 1, 15, 1, 8, 1, 13);        // FND4 SPIN 출력

            // servo 작동해도 이전 상태에 따라 LED 출력은 유지
            switch (btnPrev) {
            case 1:     // LED
                LED_PORT = 0x00;
                break;
            
            case 2:     
                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayLow) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;

            case 3:
                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayHigh) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;
            }
        }

        // Button 4 눌린 상태 + servo 미작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        else if (btn4.btnEnabled == 1 && servoEnabled == 0){
            
            // servo 가 작동하지 않게 되면 이전 상태에 따라 FND4 출렬
            // servo 작동 안해도 이전 상태에 따라 LED 출력은 유지
            switch (btnPrev) {
            case 1:
                FND4_Display(1, 18, 1, 19, 1, 14, 1, 15);   // FND4 STOP 출력

                LED_PORT = 0x00;

                break;
            
            case 2:
                FND4_Display(1, 11, 1, 14, 1, 22, 2, 0);    // FND4 LOW 출력

                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayLow) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;

            case 3:
                FND4_Display(1, 7, 1, 8, 1, 6, 1, 7);       // FND4 HIGH 출력

                LED_PORT = (1 << led_index);
                if (led_delay >= led_delayHigh) {
                    led_index++;
                    led_delay = 0;
                }
                led_delay++;
                if (led_index >= 8) {
                    led_index = 0;
                }
                break;
            }
        }

        // servo 작동 상태면 다른 버튼이 눌리기 전까지 아래 동작 계속 실행
        if (servoEnabled == 1) {
            // servo 위치를 이동 방향에 따라 변경
            servoPos += servoDiret;

            // servo 끝에 도달하면 방향 전환
            if(servoPos >= 635) {
                servoPos = 635;
                servoDiret = -1;
            }
            else if (servoPos < 105) {
                servoPos = 105;
                servoDiret = 1;
            }

            // servo 지정된 위치로 이동
            OCR1A = servoPos;
        }

        // 동작 반영 시간을 주기 위해 10 ms delay
        _delay_ms(10);
    }
}