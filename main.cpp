#include "mbed.h"
#include "MAX32630FTHR_PwmOut.h"
#include "MotorDriver.h"
#include "IMU.h"
#include "algorithm.h"

int main()
{

    // define performance parameters
    #define SAFEZONE 0.5 // [deg], This safezone is so that the motors do not buzz for normal movement
    #define PWM_cap 100 // [%], Sets the maximum allowable duty - CANNOT BE GREATER THAN 100%
    #define TILT_LIM 15 // [deg], This tilt magnitude will tell the motors to run at 100% allowable duty

    // initialize IMU
    //initIMU();
    // Maybe here we can just copy and paste the code from initIMU()?


    motor motor1(1,LED2);

    // Initialise the digital pin LED1 as an output
    //DigitalOut led(LED2);

    while(1){

        // update IMU

        // plug in new position to myalgorithm()
        myAlgorithm(ac_x,ac_y,ac_z,gy_x,gy_y,gy_z)

        // set motors()
        motor1.setDuty(duty)
    }

    return 0;
}
