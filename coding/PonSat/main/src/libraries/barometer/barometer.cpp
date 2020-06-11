#include "barometer.h"

bool Barometer::init()
{
    unsigned int b1[24];
    for (int i = 0; i < 24; i++)
    {
        Wire.beginTransmission(0x76);
        Wire.write((136 + i));
        Wire.endTransmission();
        Wire.requestFrom(0x76, 1);
        if (Wire.available() == 1)
        {
        b1[i] = Wire.read();
        }
        else return false;
    }
    dig_T1 = (b1[0] & 0xFF) + ((b1[1] & 0xFF) * 256);
    dig_T2 = b1[2] + (b1[3] * 256);
    dig_T3 = b1[4] + (b1[5] * 256);

  // pressure coefficients
    dig_P1 = (b1[6] & 0xFF) + ((b1[7] & 0xFF) * 256);
    dig_P2 = b1[8] + (b1[9] * 256);
    dig_P3 = b1[10] + (b1[11] * 256);
    dig_P4 = b1[12] + (b1[13] * 256);
    dig_P5 = b1[14] + (b1[15] * 256);
    dig_P6 = b1[16] + (b1[17] * 256);
    dig_P7 = b1[18] + (b1[19] * 256);
    dig_P8 = b1[20] + (b1[21] * 256);
    dig_P9 = b1[22] + (b1[23] * 256);

    Wire.beginTransmission(0x76);
    Wire.write(0xF4);
    Wire.write(0x27);
    Wire.endTransmission();
    Wire.beginTransmission(0x76);
    Wire.write(0xF5);
    Wire.write(0xA0);
    Wire.endTransmission();

    measure();
    h0 = getHeight();
    return true;
}

void Barometer::measure()
{
    unsigned int data[8];
    for (int i = 0; i < 8; i++)
        {
        Wire.beginTransmission(0x76);
        Wire.write((247 + i));
        Wire.endTransmission();

        Wire.requestFrom(0x76, 1);
        if (Wire.available() == 1)
        {
            data[i] = Wire.read();
        }
    }
    long adc_p = (((long)(data[0] & 0xFF) * 65536) + ((long)(data[1] & 0xFF) * 256) + (long)(data[2] & 0xF0)) / 16;
    long adc_t = (((long)(data[3] & 0xFF) * 65536) + ((long)(data[4] & 0xFF) * 256) + (long)(data[5] & 0xF0)) / 16;
    double var1 = (((double)adc_t) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
    double var2 = ((((double)adc_t) / 131072.0 - ((double)dig_T1) / 8192.0) * (((double)adc_t) / 131072.0 - ((double)dig_T1) / 8192.0)) * ((double)dig_T3);
    double t_fine = (long)(var1 + var2);
    temperature = (long)(var1 + var2);

    // Pressure offset calculations
    var1 = ((double)t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
    var2 = var2 + var1 * ((double)dig_P5) * 2.0;
    var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
    var1 = (((double) dig_P3) * var1 * var1 / 524288.0 + ((double) dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);
    double p = 1048576.0 - (double)adc_p;
    if(var1 != 0) p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    else p = 0;
    var1 = ((double) dig_P9) * p * p / 2147483648.0;
    var2 = p * ((double) dig_P8) / 32768.0;
    pressure = (uint64_t)(p + (var1 + var2 + ((double)dig_P7)) / 16.0);
}

uint32_t Barometer::getPressure()
{
    return pressure;
}

uint32_t Barometer::getTemperature()
{
    return temperature;
}
double Barometer::getHeight()
{
    return 44330 * (1.0 - pow(pressure / 101325.0, 0.1903)) - h0;
}