#include "mbed.h"
#include "max32630fthr.h"

// class motor defines a motor object
class motor {
    public:
        int motorNum;
        PwmOut pinNum;
    
    private:
        float duty;
        

    void setDuty(float duty){

        pinNum.write(duty);
        motor::duty = duty;

    };

    void printDuty(){

        printf("Motor %i current duty cycle: %f", motor::motorNum, motor::duty);

    }

};
