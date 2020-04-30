#ifndef AXISSENSOR_H
#define AXISSENSOR_H

#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C
 
#define GYRO_FULL_SCALE_250_DPS 0x00 
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18
 
#define ACC_FULL_SCALE_2_G 0x00 
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

#include <Wire.h>
#include "Arduino.h"

class MPUSensor{
    float aX, aY, aZ, gX, gY, gZ, mX, mY, mZ;
    public:
        void init();
        void measure();
        float getAcccelX();
        float getAcccelY();
        float getAcccelZ();
        float getGyroX();
        float getGyroY();
        float getGyroZ();
        float getMagX();
        float getMagY();
        float getMagZ();
        float getAccel();
        void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
        void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);     
};

#endif