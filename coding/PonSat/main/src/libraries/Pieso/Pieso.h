#ifndef PIESO_H
#define PIESO_H

#include "Arduino.h"
#include "../../config.h"

class Pieso 
{
    byte pin;
    public:
        void attach(byte p);
        void ring();
};

#endif