#ifndef BATTERYSCANNER_H
#define BATTERYSCANNER_H

#include "Arduino.h"
#include "../../config.h"

class BatteryScanner{
    byte pin;
    public:
        void attach(byte p);
        float read();
};

#endif