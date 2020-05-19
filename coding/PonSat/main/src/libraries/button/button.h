#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button
{
    byte pin;
    public:
        void attach(byte p);
        bool pressed();
};

#endif