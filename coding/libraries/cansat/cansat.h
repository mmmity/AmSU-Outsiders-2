#ifndef cansat_h
#define cansat_h

#include "Arduino.h"

#define psopin 7
#define photopin A0
#define batterypin A5
#define latchPin 8
#define clockPin 12
#define dataPin 11
#define testbuttonpin A3
#define userbuttonpin A4
#define k 0.00984375
#define deg 1

class CanSat{
	public:
		CanSat();
		static void getBattery();
		static void setPins(bool a, bool b, bool c, bool d, bool e, bool f, bool g, bool h);
		static void registerWrite(int pin, bool state);
		static void getBatteryDigit();
		//void data(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz, double* h, double* t, double* p);
	private:
		double h0;		
};
#endif
