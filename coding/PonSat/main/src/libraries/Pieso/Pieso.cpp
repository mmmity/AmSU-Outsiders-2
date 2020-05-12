#include "Pieso.h"

void Pieso::attach(byte p)
{
    pin = p;
    pinMode(pin, 1);
}

void Pieso::ring()
{
    tone(pin, TONE);
    delay(TIME_OF_TONE);
    noTone(pin);
    delay(TIME_OF_TONE);
}