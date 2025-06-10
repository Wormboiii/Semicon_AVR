#include "adc.h"

void init_ADC0() {                                      // ADC 기능을 켜고, 핀과 분주비 지정을 해주는 함수. 메인 함수에서 init_ADC0(); 로 호출하면 됨.
ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);       // ADC7번(F포트 7번핀)을 ADC 입력핀으로 설정
ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);   // ADC 프리스케일러를 64로 설정.(데이터시트에서는 50kHz~200kHz를 권장하는데 아트메가 기본 클럭 16MHz/128분주비 = 125kHz)
ADCSRA |= (1 << ADEN);                                  // ADC 켜기
}

void ADC_convert() {                                    // Analog to Digital Convert(변환)을 시작하는 함수. 메인 함수에서 ADC_convert(); 로 호출하면 됨.
    ADCSRA |= (1 << ADSC);                              // ADC 변환 시작
    while (ADCSRA & (1<< ADSC)) {                       // ADC 변환이 확실히 될때까지 기다리기

        }
}