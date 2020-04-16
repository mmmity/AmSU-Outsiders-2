#ifndef BATTERYSCANNER_H
#define BATTERYSCANNER_H

#include "../../config.h"

class BatteryScanner{
    byte pin;
    public:
        void attach(byte p);
        float read();
};

#endif