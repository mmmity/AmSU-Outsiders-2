#ifndef BAROMETER_H
#define BAROMETER_H

#include "Arduino.h"
#include <microWire.h>

class Barometer
{
    public:
    unsigned int dig_T1;
    int dig_T2;
    int dig_T3;
    unsigned int dig_P1;
    int dig_P2;
    int dig_P3;
    int dig_P4;
    int dig_P5;
    int dig_P6;
    int dig_P7;
    int dig_P8;
    int dig_P9;
    uint16_t h0 = 0;
    uint16_t pressure;
    uint64_t temperature;

    public:
        bool init();
        uint64_t getTemperature();
        uint16_t getPressure();
        uint16_t getHeight();
        void measure();
};

#endif