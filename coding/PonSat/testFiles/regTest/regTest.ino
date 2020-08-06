#include "register.h"
bool state[8] = {1, 1, 1, 1, 1, 1, 1, 1};
int fibs[16] = {0, 1, 1, 2, 3, 5, 0, 5, 5, 2, 7, 1, 0, 1, 1, 2};
Register reg;

void cleanse(bool * state)
{
  for(int i = 0; i < 8; i++)
  {
    state[i] = 0;
  }
}

void setup()
{
    reg.attach(2, 3, 4);
    
    reg.write(state);
    delay(2000);
}

void loop()
{
    for(int i = 0; i < 16; i++)
    {
      state[fibs[i]] = 1;
      reg.write(state);
      delay(2000);
      cleanse(state);
    }
}
