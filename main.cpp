#include "mbed.h"
#include "MotorDriver.h"

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

