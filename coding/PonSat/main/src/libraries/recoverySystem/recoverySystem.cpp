#include "recoverySystem.h"

void RecoverySystem::attach(byte pin1, byte pin2)
{
    srv1.attach(pin1);
    srv2.attach(pin2);
}

void RecoverySystem::init()
{
    srv1.write(SERVO_1_START_POS);
    srv2.write(SERVO_2_START_POS);
}

void RecoverySystem::recover()
{
    srv1.write(SERVO_1_REC_POS);
    srv2.write(SERVO_2_REC_POS);
}