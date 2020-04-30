#ifndef RECOVERY_SYSTEM_H
#define RECOVERY_SYSTEM_H

#include "../../config.h"
#include "Arduino.h"
#include <Servo.h>

class RecoverySystem
{
    Servo srv1;
    Servo srv2;
    public:
        void attach(byte pin1, byte pin2);
        void init();
        void recover();
};

#endif