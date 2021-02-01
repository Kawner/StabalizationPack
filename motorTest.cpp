/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "MotorDriver.h"

// Blinking rate in milliseconds
#define BLINKING_RATE     10ms


int main()
{
    // Initialise the digital pin LED1 as an output
    motor led1(1,LED1), led2(2,LED2), led3(3,LED3);

    // Test enable function, which only works as long as motor is currently disabled
    led1.enable();

    // Test disable function, which only works as long as motor is currently enabled
    led2.enable();

    led3.disable();

    while (true) {

        for (float n = 0.0;n <= 1.0;n = n + 0.01){
            led1.setDuty(1.0-n);
            led2.setDuty(n);

            ThisThread::sleep_for(BLINKING_RATE);
        }

        led1.disable();

        led3.enable();

        for (float n = 0.0;n <= 1.0;n = n + 0.01){
            led2.setDuty(1.0-n);
            led3.setDuty(n);

            ThisThread::sleep_for(BLINKING_RATE);
        }

         led2.disable();

        led1.enable();

        for (float n = 0.0;n <= 1.0;n = n + 0.01){
                led3.setDuty(1.0-n);
                led1.setDuty(n);

                ThisThread::sleep_for(BLINKING_RATE);
            }
        
        led3.disable();

        led1.enable();
    
    }

    return 0;
}
