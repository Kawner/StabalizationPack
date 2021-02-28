/**********************************************************************
This code was developed and organized by the Outer Ear Design team for the

**********************************************************************/

#include "mbed.h"                 // mbed header file
#include "MAX32630FTHR_PwmOut.h"  // PWM driver via manufacturer
#include "MotorDriver.h"          // Motor driver class developed by Miles Young

#include "bmi160.h"               // 
#include "algorithm.h"


// >> 
#define SAFEZONE 0.5 // [deg], This safezone is so that the motors do not buzz for normal movement
#define PWM_cap 100 // [%], Sets the maximum allowable duty - CANNOT BE GREATER THAN 100%
#define TILT_LIM 15 // [deg], This tilt magnitude will tell the motors to run at 100% allowable duty

float velocity(float prev_vel, float acc, float delta); 
float position(float prev_pos, float prev_vel,  float acc, float delta, float avg);
void dumpImuRegisters(BMI160 &imu);
void printRegister(BMI160 &imu, BMI160::Registers reg);
void printBlock(BMI160 &imu, BMI160::Registers startReg, BMI160::Registers stopReg);

//>>>>>>> 796634fb8c0352c192491c31978aa6f8486772a3
int main()
{
    // Initialize Motor Objects from MotorDriver.h
    motor motor0(1,LED1);
    motor motor4(1,LED2);
    motor motor2(1,LED3);

    // define performance parameters

    #define SAFEZONE 0.5 // [deg], This safezone is so that the motors do not buzz for normal movement
    #define PWM_cap 100 // [%], Sets the maximum allowable duty - CANNOT BE GREATER THAN 100%
    #define TILT_LIM 15 // [deg], This tilt magnitude will tell the motors to run at 100% allowable duty

    // initialize IMU
    //initIMU();
    // Maybe here we can just copy and paste the code from initIMU()?


    // Initialise the digital pin LED1 as an output
    //DigitalOut led(LED2);

    
    DigitalOut rLED(LED1, LED_OFF);
    DigitalOut gLED(LED2, LED_OFF);
    DigitalOut bLED(LED3, LED_OFF);
    
    I2C i2cBus(P5_7, P6_0);
    i2cBus.frequency(400000);
    BMI160_I2C imu(i2cBus, BMI160_I2C::I2C_ADRS_SDO_LO);
    
    printf("\033[H");  //home
    printf("\033[0J");  //erase from cursor to end of screen
    
    uint32_t failures = 0;
    
    if(imu.setSensorPowerMode(BMI160::GYRO, BMI160::NORMAL) != BMI160::RTN_NO_ERROR)
    {
        printf("Failed to set gyroscope power mode\n");
        failures++;
    }
    wait_us(100000);
    
    if(imu.setSensorPowerMode(BMI160::ACC, BMI160::NORMAL) != BMI160::RTN_NO_ERROR)
    {
        printf("Failed to set accelerometer power mode\n");
        failures++;
    }
    wait_us(100000);
    
    
    BMI160::AccConfig accConfig;
    //example of using getSensorConfig
    if(imu.getSensorConfig(accConfig) == BMI160::RTN_NO_ERROR)
    {
        printf("ACC Range = %d\n", accConfig.range);
        printf("ACC UnderSampling = %d\n", accConfig.us);
        printf("ACC BandWidthParam = %d\n", accConfig.bwp);
        printf("ACC OutputDataRate = %d\n\n", accConfig.odr);
    }
    else
    {
        printf("Failed to get accelerometer configuration\n");
        failures++;
    }
    
    //example of setting user defined configuration
    accConfig.range = BMI160::SENS_4G;
    accConfig.us = BMI160::ACC_US_OFF;
    accConfig.bwp = BMI160::ACC_BWP_2;
    accConfig.odr = BMI160::ACC_ODR_8;
    if(imu.setSensorConfig(accConfig) == BMI160::RTN_NO_ERROR)
    {
        printf("ACC Range = %d\n", accConfig.range);
        printf("ACC UnderSampling = %d\n", accConfig.us);
        printf("ACC BandWidthParam = %d\n", accConfig.bwp);
        printf("ACC OutputDataRate = %d\n\n", accConfig.odr);
    }
    else
    {
        printf("Failed to set accelerometer configuration\n");
        failures++;
    }
    
    BMI160::GyroConfig gyroConfig;
    if(imu.getSensorConfig(gyroConfig) == BMI160::RTN_NO_ERROR)
    {
        printf("GYRO Range = %d\n", gyroConfig.range);
        printf("GYRO BandWidthParam = %d\n", gyroConfig.bwp);
        printf("GYRO OutputDataRate = %d\n\n", gyroConfig.odr);
    }
    else
    {
        printf("Failed to get gyroscope configuration\n");
        failures++;
    }
    
    wait_us(1000000);
    printf("\033[H");  //home
    printf("\033[0J");  //erase from cursor to end of screen


    if(failures == 0)
    {
        //setup values
        float imuTemperature; 
        BMI160::SensorData accData;
        BMI160::SensorData gyroData;
        BMI160::SensorTime sensorTime;
        
        float delta;
        float avg = 0.5;
        float acc[6], vel[6], pos[6];
        float prev_time, time;
        float prev_vel[6], prev_pos[6];

        while(1)
        {
            /*
            when there is anything with UART then the whole thing is extremly slow
            remove it and it goes way faster as it is limited to the time it takes to get data from the IMU
            the I2C is at a freq of 400kHz which means somewhere hopefully around 5 samples a ms or maybe faster
            */

            //gets data from IMU Unit, currently set up for X direction accleration
            //code is set up procceedurally, set up function to do all the calcs.
            //eventually can narrow down which points are taken. Takes a lot of time to get all of the data
            //all data was stored at this point
            
            imu.getGyroAccXYZandSensorTime(accData, gyroData, sensorTime, accConfig.range, gyroConfig.range);//gets data
            //imu.getTemperature(&imuTemperature);//gets temp
            
            //gets IMU data
            acc[0] = accData.xAxis.scaled;  //x      - 0
            acc[1] = accData.yAxis.scaled;  //y      - 1
            acc[2] = accData.zAxis.scaled;  //z      - 2
            acc[3] = gyroData.xAxis.scaled; //yaw    - 3
            acc[4] = gyroData.yAxis.scaled; //pitch  - 4
            acc[5] = gyroData.zAxis.scaled; //roll   - 5
            time = sensorTime.seconds; //get time data
            delta = time - prev_time; //gets a change in time to be used in calculations


            for (int i; i < sizeof(acc); i++)
            {
                //kinematic equations
                vel[i] = velocity(prev_vel[i], acc[i], delta);
                pos[i] = position(prev_pos[i], prev_vel[i], acc[i], delta, avg);

                //set prev values
                prev_pos[i] = pos[i];
                prev_vel[i] = vel[i];
            }
                prev_time = time;            

                

            // update IMU

            // plug in new position to myalgorithm()
            myAlgorithm(pos[0],pos[1],pos[2],pos[3],pos[4],pos[5]);

            // set motors()
           // motor1.setDuty(duty);


            

            //printf("Acc = %s%f", "\033[K", acc[0]); //print acc, vel, pos
            //printf("Vel = %s%f", "\033[K", vel[0]); //broken rn so im finding other ways to store it
            //printf("Pos = %s%f", "\033[K", pos[0]);
            
            //printf("GYRO xAxis = %s%5.1f\n", "\033[K", gyroData.xAxis.scaled);
            //printf("GYRO yAxis = %s%5.1f\n", "\033[K", gyroData.yAxis.scaled);
            //printf("GYRO zAxis = %s%5.1f\n\n", "\033[K", gyroData.zAxis.scaled);
            
            //printf("Sensor Time = %s%f\n", "\033[K", sensorTime.seconds);
            //printf("Sensor Temperature = %s%5.3f\n", "\033[K", imuTemperature);

            
            //updates++;
            //printf("\033[H");
            //printf("\033[0J");  //home
            gLED = !gLED; //show code is working
            
        }
    }
    else
    {
        while(1)
        {
            rLED = !rLED;
            wait_us(250000);
        }
    }
    return 0;
}


//*****************************************************************************
float velocity(float prev_vel, float acc, float delta) //very makeshift integration function to average a lot of values
{
    return prev_vel + (acc * (delta));
    //v = v0 + at
}

//*****************************************************************************
float position(float prev_pos, float prev_vel,  float acc, float delta, float avg) //takes the average velocity of the input values
{
    return prev_pos + (prev_vel * delta) + (avg * acc * delta * delta);
    //x = x0 + v0t + 0.5at^2
}


//*****************************************************************************
void dumpImuRegisters(BMI160 &imu)
{
    printRegister(imu, BMI160::CHIP_ID);
    printBlock(imu, BMI160::ERR_REG,BMI160::FIFO_DATA);
    printBlock(imu, BMI160::ACC_CONF, BMI160::FIFO_CONFIG_1);
    printBlock(imu, BMI160::MAG_IF_0, BMI160::SELF_TEST);
    printBlock(imu, BMI160::NV_CONF, BMI160::STEP_CONF_1);
    printRegister(imu, BMI160::CMD);
    printf("\n");
}


//*****************************************************************************
void printRegister(BMI160 &imu, BMI160::Registers reg)
{
    uint8_t data;
    if(imu.readRegister(reg, &data) == BMI160::RTN_NO_ERROR)
    {
        printf("IMU Register 0x%02x = 0x%02x\n", reg, data);
    }
    else
    {
        printf("Failed to read register\n");
    }
}


//*****************************************************************************
void printBlock(BMI160 &imu, BMI160::Registers startReg, BMI160::Registers stopReg)
{
    uint8_t numBytes = ((stopReg - startReg) + 1);
    uint8_t buff[numBytes];
    uint8_t offset = static_cast<uint8_t>(startReg);
    
    if(imu.readBlock(startReg, stopReg, buff) == BMI160::RTN_NO_ERROR)
    {
        for(uint8_t idx = offset; idx < (numBytes + offset); idx++)
        {
            printf("IMU Register 0x%02x = 0x%02x\n", idx, buff[idx - offset]);
        }
    }
    else
    {
        printf("Failed to read block\n");
    }
}

