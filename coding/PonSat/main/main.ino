
#include "headers.h"

bool stp = 0, spp = 0, rcp = 0, lnp = 0;
int landingCounter = 0;

Barometer bmp;
MPUSensor mpu;
Register reg;
SerialLogger radio;
SDLogger sd;
BatteryScanner battery;
LightLevelScanner light;


void setup()
{
    pinMode(PSO_PIN, 1);
    bmp.init();
    mpu.init();
    radio.init();
    //sd.init();
    battery.attach(BATTERY_PIN);
    light.attach(LIGHT_PIN);
    reg.attach(REG_SH_PIN, REG_ST_PIN, REG_DATA_PIN);
    delay(10000);
    light.init();
}

void loop()
{
    bmp.measure();
    mpu.measure();
    
    if(rcp == 1)
    {
        if(abs(mpu.getAcccelX()) < ACCEL_LIMIT && abs(mpu.getAcccelY()) < ACCEL_LIMIT && abs(mpu.getAcccelZ()) < ACCEL_LIMIT)
        {
            landingCounter += 1;
            if(landingCounter >= 900)
            {
                lnp = 1;
                while(1)
                {
                    tone(PSO_PIN, 50);
                    delay(100);
                    noTone(PSO_PIN);
                    delay(100);
                    radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
                }
            }
        }
        else
        {
            landingCounter = 0;
        }
    }
    else
    {
        if(spp == 1)
        {
            
        }
    }
    

    radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
    delay(200);
}
