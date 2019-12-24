
#include <Wire.h>
#include <L3G.h>
L3G gyro;
void setup() {
  pinMode(A2,OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  gyro.init();
  gyro.enableDefault();
}

void loop() {
  digitalWrite(A2,HIGH);
  gyro.read();
  Serial.print((int)gyro.g.x);
  Serial.print((int)gyro.g.y);
  Serial.println((int)gyro.g.z);
  delay(100);
}
