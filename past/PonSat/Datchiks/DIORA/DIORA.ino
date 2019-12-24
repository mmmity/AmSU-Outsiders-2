#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>      
#include <Adafruit_BMP085.h>            
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_HMC5883_U.h>
#include <L3G.h>

byte rTxd = 5;
byte rRxd = 4;
SoftwareSerial radio(rTxd,rRxd);

float temp;
float Ph;
float alt;          //Переменные барометра
float seaPh;
float realAlt;


float X1;
float Y1;    
float Z1;           //Переменные акселерометра
float X;    
float Y;            
float Z;


float mX;
float mY;
float mZ;           //Переменные магнитометра
float Hdin;
float HdinDg;

float gX1;
float gY1;
float gZ1;
float gX;           //Переменные гироскопа
float gY;          
float gZ;

Adafruit_BMP085 bmp; 
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);       //Датчики
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
L3G gr;

void setup() {

  pinMode(A2,OUTPUT);
  Serial.begin(9600);
  bmp.begin();
  mag.begin();      
  accel.begin();    //Запись с датчиков
  gr.enableDefault();
  gr.init();
  Wire.begin(); 
  radio.begin(9600);
  
}

void BMP()          //Барометр
  {
    
    temp = bmp.readTemperature();
    Serial.println(temp);
    
    Ph = bmp.readPressure();
    Serial.println(Ph);

    alt = bmp.readAltitude() - 330;
    Serial.println(alt);

    seaPh = bmp.readSealevelPressure();
    Serial.println(seaPh);

    return temp;
    return Ph;
    return alt;
    return seaPh;
    
  }

  void ADXL()       //Акселерометр
  {
    
    sensors_event_t event; 
    accel.getEvent(&event);
    X = event.acceleration.x;
    Serial.println(X);
    Y = event.acceleration.y;
    Serial.println(Y);
    Z = event.acceleration.z;
    Serial.print(Z);
    Serial.println(" m/s^2 ");
    delay(500);

    return X;
    return Y;
    return Z;
    
  }

  void MGM()      //Магнитометр
  {

    sensors_event_t event;
    mag.getEvent(&event);
    
    mX = event.magnetic.x;
    mY = event.magnetic.y;
    mZ = event.magnetic.z;
    Serial.println(mX);
    Serial.println(mY);
    Serial.println(mZ);
    Serial.println(" uT");

    Hdin = atan2(event.magnetic.y, event.magnetic.x);

    float declinationAngle = 0.22;
    Hdin += declinationAngle;

    if(Hdin < 0)
      Hdin += 2*PI;
    if(Hdin > 2*PI)
      Hdin -= 2*PI;
    
    HdinDg = Hdin * 180/M_PI; 

    Serial.println(HdinDg);

    return mX;
    return mY;
    return mZ;
    return HdinDg;
    
  }

  void l3g()        //Гироскоп
  {
   
    gX = (int)gr.g.x;
    gY = (int)gr.g.y;
    gZ = (int)gr.g.z;
    return gX;
    return gY;
    return gZ;
    Serial.println(gX);
    Serial.println(gY);
    Serial.println(gZ);
    
  }

  void PADIO()
  {
    char val = 'h';
    radio.write(val);
    radio.print((char)temp);
    radio.write(ADXL);
    radio.write(MGM);
    radio.write(l3g);
    Serial.write(radio.read());
  }

  

  

void loop() {

  digitalWrite(A2,HIGH);
  BMP();
  ADXL();
  MGM();
  l3g();
  PADIO();

}
