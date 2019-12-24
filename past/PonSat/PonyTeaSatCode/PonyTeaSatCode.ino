
#include <L3G.h>
#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>      //Библиотеки
#include <Adafruit_BMP085.h>            
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_HMC5883_U.h>
#include <Servo.h>
#include <SoftwareSerial.h>

byte rSet = 6;
byte rTxd = 5;
byte rRxd = 4;      //Пины
byte photo = A0;     
byte PSo = 8;       
byte serv = 9;

bool boolA = 0;
bool boolB = 0;
bool bul = 0;
bool Stp = 0;
bool Spp = 0;
bool Rcp = 0;        //Переменные из блок-схемы
bool Lnp = 0;      
float h;
int t = 0;
int i;
int b;

float temp;
float Ph;
float alt;          //Переменные барометра
float seaPh;
float realAlt;


float A;           
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

long milis;             //Переменные из регламента


File Thelemetry;    //SD-card файл

Adafruit_BMP085 bmp; 
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);       //Датчики
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
L3G gr;

Servo srv;                      //Серво
byte pos;

SoftwareSerial radio(rTxd,rRxd); //Радиомодуль

void setup() 
  {
  Wire.begin();             //Шина

  pinMode(A3,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);        //Пины
  pinMode(13,OUTPUT);
  pinMode(photo,INPUT);         
  pinMode(7,OUTPUT);
  pinMode(PSo,OUTPUT);
  
  Serial.begin(9600);       //Запись в монитор
  
  bmp.begin();
  mag.begin();      
  accel.begin();    //Запись с датчиков
  gr.enableDefault();
  gr.init();

  SD.begin(4);      //Запись на SD-карту
  Thelemetry = SD.open("Данные.txt", FILE_WRITE);

  srv.attach(serv);   //Серво

  radio.begin(9600);      //Начало передачи данных по радиоканалу
  
  }

void sD()
  { 
    if(Thelemetry){
    Thelemetry.print("1A");
    Thelemetry.print(";");
    Thelemetry.print(milis);
    Thelemetry.print(";");
    Thelemetry.print(h);
    Thelemetry.print(";");
    Thelemetry.print(X);
    Thelemetry.print(";");
    Thelemetry.print(Y);
    Thelemetry.print(";");
    Thelemetry.print(Z);
    Thelemetry.print(";");
    Thelemetry.print(gY);
    Thelemetry.print(";");
    Thelemetry.print(gX);
    Thelemetry.print(";");
    Thelemetry.print(gZ);
    Thelemetry.print(";");
    Thelemetry.print(mX);
    Thelemetry.print(";");
    Thelemetry.print(mY);
    Thelemetry.print(";");
    Thelemetry.print(mZ);
    Thelemetry.print(";");
    Thelemetry.print(Ph);
    Thelemetry.print(";");
    Thelemetry.print(temp);
    Thelemetry.print(";");
    Thelemetry.print(Stp);
    Thelemetry.print(";");
    Thelemetry.print(Spp);
    Thelemetry.print(";");
    Thelemetry.print(Rcp);
    Thelemetry.print(";");
    Thelemetry.print(Lnp);
    Thelemetry.print(";\n");
    
    
    }
  }

void BMP()          //Барометр
  {
    
    Serial.print("Температура C = ");
    temp = bmp.readTemperature();
    Serial.println(temp);
    
    Serial.print("Давление Pa = ");
    Ph = bmp.readPressure();
    Serial.println(Ph);

    Serial.print("Высота m = ");
    alt = bmp.readAltitude() - 330;
    Serial.println(alt);
    h = alt;

    Serial.print("Давление на уровне моря(вычислено) Pa = ");
    seaPh = bmp.readSealevelPressure();
    Serial.println(seaPh);

    Serial.print("Реальная высота m = ");
    realAlt = bmp.readAltitude(101500) - 330;
    Serial.println(realAlt);

    return temp;
    return Ph;
    return alt;
    return seaPh;
    
  }

void ADXL()       //Акселерометр
  {
    
    sensors_event_t event; 
    accel.getEvent(&event);
    
    Serial.print("X: "); 
    X = event.acceleration.x;
    Serial.println(X);
    Serial.print("Y: "); 
    Y = event.acceleration.y;
    Serial.println(Y);
    Serial.print("Z: ");
    Z = event.acceleration.z;
    Serial.print(Z);
    Serial.println(" m/s^2 ");
    A = (pow(X,2)+pow(Y,2)+pow(X,2))/2;
    Serial.println(A);

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
    
    Serial.print("mX: "); Serial.println(mX);
    Serial.print("mY: "); Serial.println(mY);
    Serial.print("mZ: "); Serial.println(mZ);
    Serial.println(" uT");

    Hdin = atan2(event.magnetic.y, event.magnetic.x);

    float declinationAngle = 0.22;
    Hdin += declinationAngle;

    if(Hdin < 0)
      Hdin += 2*PI;
    if(Hdin > 2*PI)
      Hdin -= 2*PI;
    
    HdinDg = Hdin * 180/M_PI; 

    Serial.print("Heading (degrees): ");
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
    Serial.print("gX: ");
    Serial.println(gX);
    Serial.print("gY: ");
    Serial.println(gY);
    Serial.print("gZ: ");
    Serial.println(gZ);
    
  }

  void PADIO()
  {
    radio.write("1A");
    radio.write(milis);
    radio.write(h);
    radio.write(A);
    radio.write(Stp);
    radio.write(Spp);
    radio.write(Rcp);
    radio.write(Lnp);
    radio.write("\n");
    radio.print("1A");
    radio.print(milis);
    radio.print(h);
    radio.print(A);
    radio.print(Stp);
    radio.print(Spp);
    radio.print(Rcp);
    radio.print(Lnp);
    radio.print("\n");
    Serial.write(radio.read());
  }

void loop() 
    {

    if(digitalRead(12) == 1){
      digitalWrite(A1,HIGH);
      analogWrite(A3,0);
      delay(3000);
      digitalWrite(10,HIGH);
      delay(3000);
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      delay(3000);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      analogWrite(A2,255);
      srv.write(0);
      delay(3000);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      analogWrite(A2,0);
      analogWrite(A3,255);
      delay(3000);
      boolB = 1;
//      BMP();
//      ADXL();
//      MGM();
//      l3g();
//      PADIO();
    }
    else{
    if(boolB == 1){
      digitalWrite(A2,LOW);
      digitalWrite(10,LOW);
      digitalWrite(11,LOW);
      digitalWrite(A1,LOW);
      digitalWrite(A3,LOW);
      boolB = 0;
    }
    srv.write(180);
    milis = millis();
    analogWrite(13,255);
    if(boolA == 0){
    BMP();
    MGM();
    ADXL();
    l3g();
    Serial.println(h);
    delay(10000);
    boolA = 1;
    }
    
    BMP();
    ADXL();
    MGM();
    l3g();
    if(h > 5){
      if(Stp != 1){
        Stp = 1;
        analogWrite(10,255);
      }  
    }
    if(analogRead(0) > 200){
      if(Spp != 1){
        Spp = 1;
        analogWrite(10,0);
        analogWrite(11,255);
      }
      if(Rcp != 1){
        if(i >= 2){
          Serial.println("Система спасения активирована");
          srv.write(0);
          Rcp = 1;
          analogWrite(10,0);
          analogWrite(11,0);
          analogWrite(A2,255);
        }
        else{
          i += 1;
        }
      }
    }
    if(b < 1){
    X1 = X;
    Y1 = Y;       //Для просмотра движения
    Z1 = Z;
    gX1 = gX;
    gY1 = gY;
    gZ1 = gZ;
    }
    if(X1 == X && Y1 == Y && Z1 == Z && gX1 == gX && gY1 == gY && gZ1 == gZ){
      b ++;
    }
    else{
      b = 0;
    }
    if(b == 4){
      if(Lnp != 1){
        Lnp = 1;
        analogWrite(10,0);
        analogWrite(11,0);
        analogWrite(A2,0);
        analogWrite(A3,255);
        }
      Serial.println("Орём!");
      tone(PSo,3000);
      delay(50);
      noTone(PSo);
      
    }
    else
    if(t > 120){
       if(Lnp != 1){
        Lnp = 1;
        analogWrite(10,0);
        analogWrite(11,0);
        analogWrite(A2,0);
        analogWrite(A3,255);
        }
      Serial.println("Орём!");
      tone(PSo,3000);
      delay(50);
      noTone(PSo);
      
    }
    t ++; 
    sD();
    PADIO();
    delay(1000);
    }
    }
