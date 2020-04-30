#include "logger.h"

void SerialLogger::init()
{
    Serial.begin(BAUD_RATE);
}

void SerialLogger::writeCanSat(String teamID, long time, float alt, float a, bool stp, bool spp, bool rcp, bool lnp)
{
    Serial.print(teamID);
    Serial.print(";");
    Serial.print(time);
    Serial.print(";");
    Serial.print(alt);
    Serial.print(";");
    Serial.print(a);
    Serial.print(";");
    Serial.print(stp);
    Serial.print(";");
    Serial.print(spp);
    Serial.print(";");
    Serial.print(rcp);
    Serial.print(";");
    Serial.print(lnp);
    Serial.print("\n");
}