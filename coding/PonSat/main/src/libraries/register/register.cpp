#include "register.h"

void Register::attach(byte sh, byte st, byte data)
{
    sh_cp = sh;
    st_cp = st;
    ds = data;
    pinMode(sh_cp, 1);
    pinMode(st_cp, 1);
    pinMode(ds, 1);
}

void Register::write(bool state[8])
{
    for(int i = 0; i < 8; i++)
    {
        currentState[i] = state[i];
    }
    digitalWrite(st_cp, LOW);
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(sh_cp, LOW);
        digitalWrite(ds, currentState[i]);
        digitalWrite(sh_cp, HIGH);
    }
    digitalWrite(st_cp, HIGH);
}


void Register::setPin(byte pin, bool value)
{
    currentState[pin] = value;
    digitalWrite(st_cp, LOW);
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(sh_cp, LOW);
        digitalWrite(ds, currentState[i]);
        digitalWrite(sh_cp, HIGH);
    }
    digitalWrite(st_cp, HIGH);
}