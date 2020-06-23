#ifndef LOGGER_H
#define LOGGER_H
#include "../../config.h"
#include "PetitFS.h"
#include <GyverUART.h>

#define Serial uart 

class SerialLogger
{
    public:
        void init();
        void writeCanSat(String teamID, uint32_t time, uint16_t alt, uint16_t a, bool stp, bool spp, bool rcp, bool lnp);
};

class SDLogger
{
    FATFS fs;
    public:
        void init();
        void write(String str);
        void writeCanSat(String teamID, uint32_t time, uint16_t alt, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz, int16_t mx, int16_t my, int16_t mz, uint16_t pressure, uint32_t temp, bool stp, bool spp, bool rcp, bool lnp);
};

#endif