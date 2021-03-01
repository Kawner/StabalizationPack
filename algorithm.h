/* MAX32630FTHR Microcontroller main script
 * D. Choy, B. Presley, C. Sexton, M. Young -- Outer Ear Design Team
 * Project - Stabilizing vest
 * Copyright (c) 2020 Outer Ear Design Team. No use without written consent.
 */

// Import support files
#include "mbed.h"
#include <cmath>
#include <cstdio>

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
int myAlgorithm(float gy_x, float gy_y, int which_motor)
{
    // First task is to interpret the inputs
    int myMagnitude = sqrt(gy_x*gy_x + gy_y*gy_y);
    float myAngle = atan2(gy_y, gy_x);
    int AutoDuty = 0; //predefine this variable
    
    // Second task is to build a radial system that gradually adjusts the individual motor's strength. 
    // Gradual and smooth feedback will allow the patients brain to recognize new patterns and feel 
    // their movements in a more natural way... no glitchy stuff
    if(myMagnitude >= SAFEZONE) {
        if(which_motor == 0) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor0_angle)); // Autoduty for motor 0

        }
        if(which_motor == 1) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor1_angle)); // Autoduty for motor 1
        }
        if(which_motor == 2) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor2_angle)); // Autoduty for motor 2
        }
        if(which_motor == 3) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor3_angle)); // Autoduty for motor 3
        }
        if(which_motor == 4) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor4_angle)); // Autoduty for motor 4
        }
        if(which_motor == 5) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor5_angle)); // Autoduty for motor 5
        }
        if(which_motor == 6) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor6_angle)); // Autoduty for motor 6
        }
        if(which_motor == 7) {
            AutoDuty = clamp(K_p*(myMagnitude-SAFEZONE)*cos(myAngle-motor7_angle)); // Autoduty for motor 7
        }
    }
    else {
        AutoDuty = 0;
    };

    return AutoDuty;
}