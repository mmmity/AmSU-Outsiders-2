#include "recoverySystem.h"

void RecoverySystem::attach(byte p)
{
    pin = p; 
    pinMode(pin, 1);
}

void RecoverySystem::init()
{
    digitalWrite(pin, 1);
    delay(MIN_PULSE_WIDTH + STEP_WIDTH * SERVO_START_POS);
    digitalWrite(pin, 0);
    delay(PULSE_WIDTH - MIN_PULSE_WIDTH - STEP_WIDTH * SERVO_START_POS);
}

void RecoverySystem::recover()
{
    digitalWrite(pin, 1);
    delay(MIN_PULSE_WIDTH + STEP_WIDTH * SERVO_REC_POS);
    digitalWrite(pin, 0);
    delay(PULSE_WIDTH - MIN_PULSE_WIDTH - STEP_WIDTH * SERVO_REC_POS);
}