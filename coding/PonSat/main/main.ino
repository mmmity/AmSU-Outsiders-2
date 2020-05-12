
#include "headers.h"

bool stp = 0, hgp = 0, spp = 0, rcp = 0, lnp = 0;
int landingCounter = 0;
bool leds[8] = {1, 0, 0, 1, 0, 1, 0, 1};

Barometer bmp;
MPUSensor mpu;
Register reg;
SerialLogger radio;
SDLogger sd;
BatteryScanner battery;
LightLevelScanner light;
Pieso pso;
RecoverySystem rs;

void setup()
{
    rs.attach(SERVO_1_PIN, SERVO_2_PIN);
    pso.attach(PSO_PIN);
    bmp.init();
    mpu.init();
    radio.init();
    rs.init();
    //sd.init();
    battery.attach(BATTERY_PIN);
    light.attach(LIGHT_PIN);
    reg.attach(REG_SH_PIN, REG_ST_PIN, REG_DATA_PIN);
    delay(10000);
    light.init();
}

void loop()
{
    // bmp.measure();
    // mpu.measure();
    
    // if(bmp.getHeight() > 50)
    // {
    //     hgp = true;
    // }

    // if(rcp)
    // {
    //     if(abs(mpu.getAcccelX()) < ACCEL_LIMIT && abs(mpu.getAcccelY()) < ACCEL_LIMIT && abs(mpu.getAcccelZ()) < ACCEL_LIMIT)
    //     {
    //         landingCounter += 1;
    //         if(landingCounter >= 900)
    //         {
    //             lnp = 1;
    //             while(1)
    //             {
    //                 pso.ring();
    //                 radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
    //             }
    //         }
    //     }
    //     else
    //     {
    //         landingCounter = 0;
    //     }
    // }
    // else
    // {
    //     if(bmp.getHeight() < 50)
    //     {

    //     }
    //     if(light.separation())
    //     {
    //         spp = 1;
    //     }
    //     else
    //     {
    //         if(bmp.getHeight() > 5)
    //         {
    //             stp = true;
    //         }
    //     }
    // }
    

    // radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
    // delay(200);
    reg.write(leds);
    delay(1000);
}
