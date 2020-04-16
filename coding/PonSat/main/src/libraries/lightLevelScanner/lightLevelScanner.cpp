#include "lightLevelScanner.h"

void LightLevelScanner::attach(byte p)
{
    pin = p;
    pinMode(pin, 0);
}

void LightLevelScanner::init()
{
    start_value = analogRead(pin);
}

short LightLevelScanner::read()
{
    return analogRead(pin) - start_value;
}

bool LightLevelScanner::separation()
{
    return read() > LIMIT_LIGHT_LEVEL;
}