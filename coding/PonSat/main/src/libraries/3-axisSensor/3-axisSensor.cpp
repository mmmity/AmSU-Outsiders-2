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

int16_t MPUSensor::getAcccelX()
{
    return aX;
}

int16_t MPUSensor::getAcccelY()
{
    return aY;
}

int16_t MPUSensor::getAcccelZ()
{
    return aZ;
}

int16_t MPUSensor::getGyroX()
{
    return gX;
}

int16_t MPUSensor::getGyroY()
{
    return gY;
}

int16_t MPUSensor::getGyroZ()
{
    return gZ;
}

int16_t MPUSensor::getMagX()
{
    return mX;
}

int16_t MPUSensor::getMagY()
{
    return mY;
}

int16_t MPUSensor::getMagZ()
{
    return mZ;
}

uint16_t MPUSensor::getAccel()
{
    return (uint16_t)sqrt(aX * aX + aY * aY + aZ * aZ);
}