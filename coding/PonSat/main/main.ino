#include "src/config.h"
#include "src/logger.cpp"
#include "src/libraries/register/register.h"
#include "src/libraries/batteryScanner/batteryScanner.h"
#include "src/libraries/barometer/barometer.h"
#include "src/libraries/3-axisSensor/3-axisSensor.h"

Barometer bmp;
MPUSensor mpu;
Register reg;

void setup()
{
    Serial.begin(9600);
    Serial.println("Begin");
    bmp.init();
    mpu.init();
    reg.attach(12, 8, 11);
}

void loop()
{
    reg.write(0b10101010);
    delay(1000);
    reg.write(0b01010101);
    delay(1000);
    // bmp.measure();
    // mpu.measure();
    // Serial.print("A1;");
    // Serial.print(millis());
    // Serial.print(";");
    // Serial.print("dummy;");
    // Serial.print(mpu.getAcccelX());
    // Serial.print(';');
    // Serial.print(mpu.getAcccelY());
    // Serial.print(';');
    // Serial.print(mpu.getAcccelZ());
    // Serial.print(';');
    // Serial.print(mpu.getGyroX());
    // Serial.print(';');
    // Serial.print(mpu.getGyroY());
    // Serial.print(';');
    // Serial.print(mpu.getGyroZ());
    // Serial.print(';');
    // Serial.print(mpu.getMagX());
    // Serial.print(';');
    // Serial.print(mpu.getMagY());
    // Serial.print(';');
    // Serial.print(mpu.getMagZ());
    // Serial.print("\n");
    // delay(1000);

}
