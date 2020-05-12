#ifndef REGISTER_H
#define REGISTER_H
#include "Arduino.h"
class Register
{
    byte sh_cp, st_cp, ds;
    bool currentState[8];
    public:
        void attach(byte sh, byte st, byte data);
        void write(bool state[8]);
        void setPin(byte pin, bool value);
};

#endif