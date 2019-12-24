
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
void setup(void) 
{
  pinMode(A2,OUTPUT);
  Serial.begin(9600);
  mag.begin();
}

void loop(void) 
{
  digitalWrite(A2,HIGH);
  sensors_event_t event; 
  mag.getEvent(&event);
  Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;
  if(heading < 0)
    heading += 2*PI;
  if(heading > 2*PI)
    heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI; 
  
  Serial.println(headingDegrees);
  
  delay(500);
}
