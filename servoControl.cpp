#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "lib/ServoControl/ServoControl.h"

int main()
{

    stdio_init_all();

    ServoControl servo = ServoControl(25);

    while(1) {
    
        servo.setAngle(0);
        sleep_ms(1000);
        servo.setAngle(90);
        sleep_ms(1000);
        servo.setAngle(180);
        sleep_ms(1000);
    }

    return 0;
}
