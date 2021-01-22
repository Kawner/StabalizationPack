#include "mbed.h"
#include "max32630fthr.h"

// class motor defines a motor object
class motor {
    public:
    // Constructor prints startup messages
    motor(){
        printf("\r\n");
        printf("Motor object created \r\n");
        printf("Please assign motor number and pin\r\n");
        printf("\r\n");
    }
        // Assign identifying number with which to keep track of motor object
        int motorNum;
        // Assign output pin used to send PWM signal to motor from MAX32630FTHR
        PinName pinNum;
        // Initialize PWM pin
        PwmOut pwmout_init(pwmout_t *pwmPin, PinName pinNum);
        float curduty = pwmout_read(pwmout_t *pwmPin);


    void setDuty(float duty){

        printf("PinNum: %i \r\n", pinNum);
        printf("New duty cycle: %f", duty);
        pwmout_write(pwmout_t *pinOut, duty);
    
    };

    void printDuty(){

        float curduty = pwmout_read(pwmout_t *pwmPin);

        printf("Motor %i ", motorNum);
        printf("current duty cycle: %0.2f %% \r\n", curduty);

    }

};
