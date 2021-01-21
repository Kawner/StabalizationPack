#include "mbed.h"
#include "max32630fthr.h"
#include "MotorDriver.h"

// main() runs in its own thread in the OS
int main()
{
    // create motor object
    motor motor1;
    // assign motor number
    motor1.motorNum = 1;
    // assign motor pin
    motor1.pinNum = LED1;

    float duty = 0.50;
    // set motor duty cycle
    motor1.setDuty(duty);
    motor1.printduty();

    return 0;
};

