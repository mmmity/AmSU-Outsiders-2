// OwO
// Все константы есть в файле Config.h 

#include "headers.h"                        // Там тоже весело

bool stp = 0, spp = 0, rcp = 0, lnp = 0;    // Фазы полета       
int testModeCounter = 0;                    // Счетчик для обеспечения задержек в тестовом режиме
bool leds[8] = {1, 1, 0, 0, 0, 0, 0, 0};    // Массив значений регистра

Barometer bmp;
MPUSensor mpu;
Register reg;
SerialLogger radio;
SDLogger sd;
BatteryScanner battery;
LightLevelScanner light;                    // Объявление объектов
Pieso pso;                                  // Все классы писал сам UwU
RecoverySystem rs;
Button testBtn;
Button userBtn;

void setup()
{
    Wire.begin();                           // Здесь запускаем I2C
    rs.attach(SERVO_PIN);
    pso.attach(PSO_PIN);
    bmp.init();
    mpu.init();                             // Просто посмотрите на это
    radio.init();                           // Все названия методов стандартизированы
    rs.init();                              // Шикарно :)
    sd.init();
    testBtn.attach(TEST_BUTTON_PIN);
    userBtn.attach(USER_BUTTON_PIN);
    battery.attach(BATTERY_PIN);
    light.attach(LIGHT_PIN);
    reg.attach(REG_SH_PIN, REG_ST_PIN, REG_DATA_PIN);
    
    for(int i = 0; i < int(battery.read() / 12); i++)
    {
        leds[i] = 1;
    }
    reg.write(leds);
    delay(2000);
    leds[0] = 1;
    leds[1] = 1;
    for(int i = 2; i < 8; i++) leds[i] = 0;
    reg.write(leds);
    delay(8000);
    light.init();                           // А фоторезистор инициализируем после укомплектации
    leds[2] = 1;
}

void loop()
{
    if (testBtn.pressed())
    {
        leds[3] = 1;
        mpu.measure();
        if (mpu.getAcccelX() > 20000)
        {
            leds[4] = 1;
        }
        if (light.separation())
        {
            leds[5] = 1;
            if(testModeCounter >= 25)
            {
                rs.recover();
                leds[6] = 1;
            }
            if (testModeCounter >= 50) leds[7] = 1;
            testModeCounter ++ ;
        }
    }
    else 
    {
      for(int i = 3; i < 8; i ++) leds[i] = 0;
        bmp.measure();
        mpu.measure();

        if(lnp)
        {
            while(1)
            {
                pso.ring();         // Всё нормально, задержка есть в методе ring
            }
        }
        
            if(spp)                         // Ждем-с 50 метров, а потом спасаемся
            {                               // c:
                if(bmp.getHeight() <= 50)
                {
                    rcp = 1;
                    leds[6] = 1;
                    rs.recover();            // Максимальная абстракция OwO
                }
                if(bmp.getHeight() <= 5)
                {
                    lnp = 1;
                }
            }
            else                            
            {
                if(light.separation())       // Я просто поражаюсь этой абстракции UwU
                {
                    spp = 1;
                    leds[5] = 1;            // Я думаю эта команда точно выиграет  
                }
            }                               // И вообще, они мои любимчики теперь <3
        
        if(mpu.getAccel() > 20000)           // Проверяем на резкое ускорение
        {                                    // Если да, то спутник взлетел
            stp = 1;
            leds[4] = 1;
        }
        radio.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAccel(), stp, spp, rcp, lnp);
        sd.writeCanSat(TEAM_ID, millis(), bmp.getHeight(), mpu.getAcccelX(), mpu.getAcccelY(), mpu.getAcccelZ(), mpu.getGyroX(), mpu.getGyroX(), mpu.getGyroZ(), mpu.getMagX(), mpu.getMagY(), mpu.getMagZ(), bmp.getPressure(), bmp.getTemperature(), stp, spp, rcp, lnp);
    }
    reg.write(leds);
    delay(200);
}
