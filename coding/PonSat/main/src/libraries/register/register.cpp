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

void Register::write(byte bin)
{
    current_state = bin;
    digitalWrite(st_cp, LOW);
    shiftOut(ds, sh_cp, MSBFIRST, bin);
    digitalWrite(st_cp, HIGH);
}

byte Register::read()
{
    return current_state;
}

void Register::setPin(byte pin, bool value)
{
    if(value == true){
        write((read() || pow(2, pin)));
    }
    else{
        write((read() && 255 - pow(2, pin)));
    }
}