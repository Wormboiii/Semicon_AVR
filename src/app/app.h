#ifndef __APP_H__
#define __APP_H__

#include "../driver/led.h"
#include "../driver/button.h"
#include "../driver/pwm8b.h"
#include "../driver/pwm16b.h"
#include "../driver/fnd.h"
#include "../driver/adc.h"

void app_init();
void app_main();

#endif /* __APP_H__ */