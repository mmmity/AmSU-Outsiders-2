#include "button.h"

void Button::attach(byte p)
{
    pin = p;
    pinMode(pin, 0);
}

bool Button::pressed()
{
    return digitalRead(pin);
}