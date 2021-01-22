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
    motor1.pinNum = P5_7;

    int flag = 0;

    while (true) {
        // set motor duty cycle
        
        motor1.setDuty(0.50f);

        //if (flag == 0) {
        //    motor1.setDuty(0.1f);
        //    flag = 1;
        //    wait_us(100000);
        //}
        
        //else if (flag == 1) {
        //    motor1.setDuty(0.9f);
        //    flag = 0;
        //    wait_us(100000);
        //}

        motor1.printDuty();
    }
    
    return 0;
};

