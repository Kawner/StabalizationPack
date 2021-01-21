#include "mbed.h"
#include "max32630fthr.h"

// class motor defines a motor object
class motor {
    public:
    motor(){
        printf("\r\n");
        printf("Motor object created \r\n");
        printf("Please assign motor number and pin\r\n");
        printf("\r\n");
    }
        
        int motorNum;
        PinName pinNum;
        PwmOut led(PinName pinNum);
        float duty = 0.99;
        
    void setDuty(float duty_in){

        duty = duty_in;
        printf("PinNum: %i \r\n", pinNum);
        PwmOut led(pinNum);
        led.write(duty_in);
    
    };

    void printDuty(){

        printf("Motor %i ", motorNum);
        printf("current duty cycle: %0.2f", duty);

    }

};
