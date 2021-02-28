/* MAX32630FTHR Microcontroller main script
 * D. Choy, B. Presley, C. Sexton, M. Young -- Outer Ear Design Team
 * Project - Stabilizing vest
 * Copyright (c) 2020 Outer Ear Design Team. No use without written consent.
 */

// Import support files
#include "mbed.h"
#include <cmath>
#include <cstdio>

// define LED Blinking rate in milliseconds
#define BLINKING_RATE     100ms 
// define PI
#define PI 3.141592654

// define location of motors on vest
#define motor0_angle 90
#define motor1_angle 135
#define motor2_angle 180
#define motor3_angle -135
#define motor4_angle -90
#define motor5_angle -45
#define motor6_angle 0
#define motor7_angle 45

// define performance parameters
#define SAFEZONE 0.5 // [deg], This safezone is so that the motors do not buzz for normal movement
#define PWM_cap 100 // [%], Sets the maximum allowable duty - CANNOT BE GREATER THAN 100%
#define TILT_LIM 15 // [deg], This tilt magnitude will tell the motors to run at 100% allowable duty

// define consequential constants
float K_p = 100*(PWM_cap/100)/(TILT_LIM-SAFEZONE);

//create a PWM clamp function - keep it between 0 and the set maximum!
int clamp(float value) {
    if(value <= 0) {
        return 0;
    } else if (value >= PWM_cap) {
        return PWM_cap;
    } else {
        return int(value);
    }
}

// Create the algorithm function that runs in infinite while loop
void myAlgorithm(float ac_x, float ac_y, float ac_z, float gy_x, float gy_y, float gy_z)
{
    // First task is to interpret the inputs
    int myMagnitude = sqrt(gy_x*gy_x + gy_y*gy_y);
    float myAngle = atan2(ac_y, ac_x);
    
    // Second task is to build a radial system that gradually adjusts the individual motor's strength. 
    // Gradual and smooth feedback will allow the patients brain to recognize new patterns and feel 
    // their movements in a more natural way... no glitchy stuff
    if(myMagnitude >= SAFEZONE) {
        int AutoDuty_0 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor0_angle)); // Autoduty for motor 0
        int AutoDuty_1 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor1_angle)); // Autoduty for motor 1
        int AutoDuty_2 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor2_angle)); // Autoduty for motor 2
        int AutoDuty_3 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor3_angle)); // Autoduty for motor 3
        int AutoDuty_4 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor4_angle)); // Autoduty for motor 0
        int AutoDuty_5 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor5_angle)); // Autoduty for motor 0
        int AutoDuty_6 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor6_angle)); // Autoduty for motor 0
        int AutoDuty_7 = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor7_angle)); // Autoduty for motor 0
    }

    // Third task is to run Miles' set duty motor functions
    

}
