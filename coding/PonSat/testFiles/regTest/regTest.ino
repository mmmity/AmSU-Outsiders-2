#include "../../main/src/libraries/register/register.h"

Register reg;

void setup()
{
    reg.attach(12, 8, 11);
}

void loop()
{
    reg.write(0b11111111);
}