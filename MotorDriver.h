#include "mbed.h"
#include"MAX32630FTHR_PwmOut.h"


// class motor creates a vibrational motor object which is controlled through PWM
class motor : virtual public MAX32630FTHR_PwmOut {
    public:
        // Motor designator
        int num;

    // Constructor accepts and assigns motor designation number and pin to PWM variable
    motor(int motorNum, PinName pinNum) : MAX32630FTHR_PwmOut(pinNum)
    {  
        // Constructor input gives designation number to motor object
        num = motorNum;
        printf("\r\nMotor assigned number %i \r\n", num);

        // Assign output pin used to send PWM signal to motor from MAX32630FTHR
        // pin = MAX32630FTHR_PwmOut(pinNum);
        printf("Pin %i assigned for motor %i PWM output \r\n", pinNum, num);
        printf("\r\n");
    }   

    void enable(){

        this->unlock_deep_sleep();
        printf("Motor enabled");
        
    }    

    void disable(){

        this->lock_deep_sleep();
        printf("Motor disabled");

    }

    void setDuty(float newDuty){


        printf("Motor %i duty cycle set to: %F", num, newDuty);
        this->write(newDuty);
    
    }

    void printDuty(){

        float currDuty = this->read();
        printf("Motor %i current duty cycle: %0.2F %% \r\n", num, currDuty);

    }

};
