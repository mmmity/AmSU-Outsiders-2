#include "cansat.h"

CanSat::CanSat(){
	
}
void CanSat::getBattery(){
  static double a_y;
  float voltage = k * analogRead(batterypin);
  a_y = a_y - 0.3 * (a_y - voltage);
  double chargeLevel = a_y / 8.4 * 100;
  if(chargeLevel > 0 && chargeLevel < 10) setPins(1, 0, 0, 0, 0, 0, 0, 0);
  else if(chargeLevel >= 10 && chargeLevel < 23) setPins(1, 1, 0, 0, 0, 0, 0, 0);
  else if(chargeLevel >= 23 && chargeLevel < 36) setPins(1, 1, 1, 0, 0, 0, 0, 0);
  else if(chargeLevel >= 36 && chargeLevel < 49) setPins(1, 1, 1, 1, 0, 0, 0, 0);
  else if(chargeLevel >= 49 && chargeLevel < 62) setPins(1, 1, 1, 1, 1, 0, 0, 0);
  else if(chargeLevel >= 62 && chargeLevel < 75) setPins(1, 1, 1, 1, 1, 1, 0, 0);
  else if(chargeLevel >= 75 && chargeLevel < 90) setPins(1, 1, 1, 1, 1, 1, 1, 0);
  else if(chargeLevel >= 90) setPins(1, 1, 1, 1, 1, 1, 1, 1);
  else if(chargeLevel <= 0) setPins(0, 0, 0, 0, 0, 0, 0, 0);
}
void CanSat::getBatteryDigit(){
  float voltage = k * analogRead(batterypin);
  static double b_y;
  b_y = b_y - 0.3 * (b_y - voltage);
  double chargeLevel = b_y / 8.4 * 100;
  if(chargeLevel <= 50) registerWrite(0, 0);
  else registerWrite(0, 1);
}
void CanSat::registerWrite(int pin, bool state){
  byte bitsToSend = 0;
  digitalWrite(8, LOW);
  bitWrite(bitsToSend, pin, state);
  shiftOut(11, 12, MSBFIRST, bitsToSend);
  digitalWrite(8, HIGH);
}
void CanSat::setPins(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h){
  registerWrite(0, a);
  registerWrite(1, b);
  registerWrite(2, c);
  registerWrite(3, d);
  registerWrite(4, e);
  registerWrite(5, f);
  registerWrite(6, g);
  registerWrite(7, h);
}
