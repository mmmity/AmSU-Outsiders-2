#ifndef LIGHT_LEVEL_SCANNER_H
#define LIGHT_LEVEL_SCANNER_H

#include "../../config.h"
#include "Arduino.h"

class LightLevelScanner{
    byte pin;
    short start_value;
    public:
        void attach(byte p);
        void init();
        short read();
        bool separation();
};

#endif