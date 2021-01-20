#include "mbed.h"

// class motor defines a motor object
class motor {
    public:
        int motorNum;
        timer ;
        pin
        PwmOut led(int pinA);

    void setDuty(float duty){
        
        // sets the duty cycle for vibrational motor PWM
        digitalWrite(pin,duty);
    };
};