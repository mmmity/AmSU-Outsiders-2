#ifndef RECOVERY_SYSTEM_H
#define RECOVERY_SYSTEM_H

#include "../../config.h"
#include "Arduino.h"

class RecoverySystem
{
    byte pin;
    public:
        void attach(byte p);
        void init();
        void recover();
};

#endif