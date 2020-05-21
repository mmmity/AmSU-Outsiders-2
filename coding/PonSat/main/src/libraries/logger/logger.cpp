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

void SDLogger::init()
{
    while (pf_mount(&fs));
    while (pf_open("FILE.TXT"));
}

void SDLogger::write(String str)
{
    uint8_t buf [str.length()];
    for(int i = 0; i < str.length(); i++)
    {
        buf[i] = str[i];
    }
    UINT nr;
    pf_write(buf, sizeof(buf), &nr);
}

void SDLogger::writeCanSat(String teamID, long time, float alt, float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz, float pressure, bool stp, bool spp, bool rcp, bool lnp)
{
    write(teamID);
    write(";");
    write(String(time));
    write(";");
    write(String(alt));
    write(";");
    write(String(ax));
    write(";");
    write(String(ay));
    write(";");
    write(String(az));
    write(";");
    write(String(gx));
    write(";");
    write(String(gy));
    write(";");
    write(String(gz));
    write(";");
    write(String(mx));
    write(";");
    write(String(my));
    write(";");
    write(String(mz));
    write(";");
    write(String(pressure));
    write(";");
    write(String(stp));
    write(";");
    write(String(spp));
    write(";");
    write(String(rcp));
    write(";");
    write(String(lnp));
    write("\n");
}