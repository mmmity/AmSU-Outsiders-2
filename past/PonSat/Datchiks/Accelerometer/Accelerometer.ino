#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


void setup(void) 
{
  Serial.begin(9600);
  accel.begin();
  accel.setRange(ADXL345_RANGE_16_G);
  pinMode(A2,OUTPUT);
}

void loop(void) 
{
  digitalWrite(A2,HIGH);
  sensors_event_t event; 
  accel.getEvent(&event);
  Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("м/с^2 ");
  delay(100);
}
