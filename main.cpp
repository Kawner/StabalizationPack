#include "mbed.h"

// class motor defines a motor object
class motor {
    public:
        int motorNum;
        pin
        PwmOut led(int pinA);

    void setDuty(float duty){
        
        // sets the duty cycle for vibrational motor PWM
        digitalWrite(pin,duty);
    };
};


// main() runs in its own thread in the OS
int main()
{
    // create motor object
    motor motor1;
    // assign motor number
    motor1.motorNum = 1;
    // assign motor pin
    motor1.pinA = LED1;
    // set motor duty cycle
    motor1.setDuty(50);

    return 0;
};

