#include <barometer.h>
Barometer bmp;
void setup() {
  Serial.begin(9600);
  Serial.println("starting");
  // put your setup code here, to run once:
  bmp.init();
  bmp.measure();
  Serial.println("started");
}

void loop() {
  // put your main code here, to run repeatedly:
//  bmp.measure();
//  Serial.print(bmp.getHeight());
//  Serial.print(" ");
//  Serial.print(bmp.getPressure());
//  Serial.print(" ");
//  Serial.println(bmp.getTemperature());
//  delay(200);
}
