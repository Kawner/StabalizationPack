#include "mbed.h"
#include"MAX32630FTHR_PwmOut.h"
// #include "MotorDriver.h"
MAX32630FTHR_PwmOut led = MAX32630FTHR_PwmOut(LED2);
 
 int main()
 {
     float dc;
     unsigned int idx = 0;
 
     while (1) {
         for (dc = 0.0f; dc <= 1.0f; dc += 0.1f) {
             led.write(dc);
             wait_us(idx*1000000);
         }
         idx++;

         if(idx == 10){
             idx = 0;
         }
    }
    return 0;
};