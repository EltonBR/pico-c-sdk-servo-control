#include "ServoControl.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define SERVO_SYS_CLK_REF 125e6

ServoControl::ServoControl(uint GPIO) {
    this->gpio = GPIO;
    this->pwm_wrap = 62500;

    gpio_set_function(this->gpio, GPIO_FUNC_PWM);
    this->slice_num = pwm_gpio_to_slice_num(this->gpio);
    this->pwm_conf = pwm_get_default_config();
    pwm_config_set_clkdiv_mode(&this->pwm_conf, PWM_DIV_FREE_RUNNING);
    pwm_config_set_clkdiv_int(&this->pwm_conf, 40);
    pwm_config_set_wrap(&this->pwm_conf, this->pwm_wrap);
    pwm_init(this->slice_num, &this->pwm_conf, 1);
    pwm_set_chan_level(this->slice_num, pwm_gpio_to_channel(this->gpio), 3125+1562);
}

void ServoControl::setAngle(uint16_t angle) {
    pwm_set_chan_level(this->slice_num, pwm_gpio_to_channel(this->gpio), 3125+(17*angle));
}