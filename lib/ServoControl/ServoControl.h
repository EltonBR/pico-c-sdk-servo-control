#ifndef __SERVO_CONTROL__H
#define __SERVO_CONTROL__H

class ServoControl {
    private: uint slice_num;
    private: pwm_config pwm_conf;
    private: uint gpio;
    private: uint16_t pwm_wrap;
    public: ServoControl(uint GPIO);
    public: void setAngle(uint16_t angle);
};

#include "ServoControl.cpp"
#endif