#include "batteryScanner.h"

void BatteryScanner::attach(byte p)
{
    pin = p;
}
float BatteryScanner::read()
{
    float voltage = analogRead(pin) * 5.0 / 1024;
    return (voltage - ACCUMULATOR_LOWER_LIMIT) / (ACCUMULATOR_UPPER_LIMIT - ACCUMULATOR_LOWER_LIMIT);
}