#include "recoverySystem.h"

void Servo::attach(byte pin)
{
    this->pin = pin;
    pinMode(pin, 1);
}

void Servo::write(int steps) // 1 step = 10 degrees
{
    pos = steps;
    digitalWrite(pin, 1);
    int time = MIN_PULSE_WIDTH + STEP_WIDTH * steps;
    delayMicroseconds(time);
    digitalWrite(pin, 0);
    delayMicroseconds(PULSE_WIDTH - time);
}

int Servo::getPos()
{
    return pos;
}