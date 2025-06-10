#ifndef __ADC_H__
#define __ADC_H__

#include "../common/def.h"

void init_ADC0();       // ADC 기능을 켜고, 핀과 분주비 지정을 해주는 함수. 메인 함수에서 init_ADC0(); 로 호출하면 됨.
void ADC_convert();     // Analog to Digital Convert(변환)을 시작하는 함수. 메인 함수에서 ADC_convert(); 로 호출하면 됨.

#endif /* __ADC_H__ */