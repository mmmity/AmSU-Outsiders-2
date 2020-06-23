#include <barometer.h>
Barometer bmp;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  bmp.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  bmp.measure();
  Serial.println(bmp.getHeight());
  delay(200);
}
