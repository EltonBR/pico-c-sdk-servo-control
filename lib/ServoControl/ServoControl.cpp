#include "ServoControl.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define SERVO_SYS_CLK_REF 125e6

#define MINIMAL_PWM_WIDTH 3125
#define SERVO_90DEG 1562
#define ANGLE_STEP 17
#define PWM_WRAP 62500
#define PWM_CLOCK_DIVIDER 40
// sysclock is 125mhz, pwm freq is (sysclock/PWM_CLOCK_DIVIDER)/PWM_WRAP = 50hz

ServoControl::ServoControl(uint GPIO) {
    this->gpio = GPIO;
    this->pwm_wrap = PWM_WRAP;

    gpio_set_function(this->gpio, GPIO_FUNC_PWM);
    this->slice_num = pwm_gpio_to_slice_num(this->gpio);
    this->pwm_conf = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&this->pwm_conf, PWM_DIV_FREE_RUNNING);
    pwm_config_set_clkdiv_int(&this->pwm_conf, PWM_CLOCK_DIVIDER);
    pwm_config_set_wrap(&this->pwm_conf, this->pwm_wrap);
    pwm_init(this->slice_num, &this->pwm_conf, 1);
    pwm_set_chan_level(this->slice_num, pwm_gpio_to_channel(this->gpio), MINIMAL_PWM_WIDTH+SERVO_90DEG);
}

void ServoControl::setAngle(uint16_t angle_in_degree) {
    pwm_set_chan_level(this->slice_num, pwm_gpio_to_channel(this->gpio), MINIMAL_PWM_WIDTH+(ANGLE_STEP*angle_in_degree));
}