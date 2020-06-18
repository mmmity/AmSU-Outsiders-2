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
        void writeCanSat(String teamID, long time, double alt, uint32_t a, bool stp, bool spp, bool rcp, bool lnp);
};

class SDLogger
{
    FATFS fs;
    public:
        void init();
        void write(String str);
        void writeCanSat(String teamID, long time, double alt, uint32_t ax, uint32_t ay, uint32_t az, uint32_t gx, uint32_t gy, uint32_t gz, uint32_t mx, uint32_t my, uint32_t mz, uint32_t pressure, uint32_t temp, bool stp, bool spp, bool rcp, bool lnp);
};

#endif