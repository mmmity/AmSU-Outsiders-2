// OwO
// Все константы есть в файле Config.h 

#include "headers.h"                        // Там тоже весело

bool stp = 0, spp = 0, rcp = 0, lnp = 0;    // Фазы полета
int landingCounter = 0;                     // Счетчик для определения факта приземления
bool leds[8] = {1, 0, 0, 1, 0, 1, 0, 1};    // Массив значений регистра

Barometer bmp;
MPUSensor mpu;
Register reg;
SerialLogger radio;
SDLogger sd;
BatteryScanner battery;
LightLevelScanner light;                    // Объявление объектов
Pieso pso;                                  // Все классы писал сам UwU
RecoverySystem rs;

void setup()
{
    rs.attach(SERVO_PIN);
    pso.attach(PSO_PIN);
    bmp.init();
    mpu.init();                             // Просто посмотрите на это
    radio.init();                           // Все названия методов стандартизированы
    rs.init();                              // Шикарно :)
    //sd.init();
    battery.attach(BATTERY_PIN);
    light.attach(LIGHT_PIN);
    reg.attach(REG_SH_PIN, REG_ST_PIN, REG_DATA_PIN);
    delay(10000);
    light.init();                           // А фоторезистор инициализируем после укомплектации
}

void loop()
{
    bmp.measure();
    mpu.measure();
    
    if(rcp) // Проверка на приземление
    {
        if(abs(mpu.getAcccelX()) < ACCEL_LIMIT && abs(mpu.getAcccelY()) < ACCEL_LIMIT && abs(mpu.getAcccelZ()) < ACCEL_LIMIT)
        {
            landingCounter += 1;
            if(landingCounter >= 900)   // Думаю, трех минут хватит
            {
                lnp = 1;
                while(1)
                {
                    pso.ring();         // Всё нормально, задержка есть в методе ring
                    radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
                }
            }
        }
        else
        {
            landingCounter = 0;
        }
    }
    else                                // Чтобы не повторять один и тот же код когда он не нужен
    {
        if(spp)                         // Ждем-с 50 метров с:
        {
            if(bmp.getHeight() <= 50)
            {
                rcp = 1;
                rs.recover();            // Максимальная абстракция OwO
            }
        }
        else                             // Уходим вглубь...
        {
            if(light.separation())       // Я просто поражаюсь этой абстракции UwU
            {
                spp = 1;
            }
        }                                // Я думаю эта команда точно выиграет
    }                                    // И вообще, они мои любимчики теперь <3
    
    if(bmp.getHeight() > 5)              // По-моему 5 - идеальный выбор
    {                                    // Надо было запихать в константу HEIGHT_LIMIT
        stp = 1;
    }
    

    radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
    delay(200);
}
