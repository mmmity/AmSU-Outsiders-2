#include "3-axisSensor.h"

void MPUSensor::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    // Read Nbytes
    Wire.requestFrom(Address, Nbytes); 
    uint8_t index=0;
    while (Wire.available())
    Data[index++]=Wire.read();
}

void MPUSensor::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();
}

void MPUSensor::init()
{
    Wire.begin();
    I2CwriteByte(MPU9250_ADDRESS,29,0x06);
    I2CwriteByte(MPU9250_ADDRESS,26,0x06);
    
    I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_1000_DPS);
    I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
    I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);
    I2CwriteByte(MAG_ADDRESS,0x0A,0x16);
}

void MPUSensor::measure()
{
    uint8_t Buf[16];
    I2Cread(MPU9250_ADDRESS,0x3B,16,Buf);
    aX=-(Buf[0]<<8 | Buf[1]);
    aY=-(Buf[2]<<8 | Buf[3]);
    aZ=Buf[4]<<8 | Buf[5];

    gX=-(Buf[8]<<8 | Buf[9]);
    gY=-(Buf[10]<<8 | Buf[11]);
    gZ=Buf[12]<<8 | Buf[13];

    uint8_t ST1;
    do
    {
        I2Cread(MAG_ADDRESS,0x02,1,&ST1);
    }
    while (!(ST1&0x01));

    uint8_t Mag[8]; 
    I2Cread(MAG_ADDRESS,0x03,8,Mag);

    mX=-(Mag[3]<<8 | Mag[2]);
    mY=-(Mag[1]<<8 | Mag[0]);
    mZ=-(Mag[5]<<8 | Mag[4]);
}

float MPUSensor::getAcccelX()
{
    return aX;
}

float MPUSensor::getAcccelY()
{
    return aY;
}

float MPUSensor::getAcccelZ()
{
    return aZ;
}

float MPUSensor::getGyroX()
{
    return gX;
}

float MPUSensor::getGyroY()
{
    return gY;
}

float MPUSensor::getGyroZ()
{
    return gZ;
}

float MPUSensor::getMagX()
{
    return mX;
}

float MPUSensor::getMagY()
{
    return mY;
}

float MPUSensor::getMagZ()
{
    return mZ;
}