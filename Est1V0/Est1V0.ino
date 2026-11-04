/*
Codigo orientado para Atmega8266
integración de sensores para recolección de datos
DHT22
GUVA
BH1750
Openlog

salida de pines: 
led testigo: codigo de colores
DHT -> 4
guva -> A0
BH1750 I2C

open log at (RX,TX) = (10,11) 

*/

// #include <time.h> solve time with RTC


#include <Wire.h>
#include <SoftwareSerial.h>


#include <DHT.h>
#include <GUVA-S12SD.h>
#include <BH1750.h>


#define DHTPIN221 4
#define DHTTYPE221 DHT22

DHT dht221(DHTPIN221, DHTTYPE221);

GUVAS12SD uv(A0);
BH1750 lightMeter;

SoftwareSerial openLog(10, 11);


void setup(){
  Serial.begin(9600);
  openLog.begin(9600);
  delay(2000);
  Wire.begin();

  dht221.begin();
  //Serial.println(F("DHTbegin"));
  lightMeter.begin();
  
  //Serial.print(F("Piramometer begin"));
  Serial.println("HUM, TEMP, VR, UV, lx");
  openLog.println("HUM, TEMP, VR, UV, lx");
  delay(100);
  //openLog.println();
}

void loop(){

  float hum = dht221.readHumidity();
  float temp = dht221.readTemperature();
  
  float mV = uv.read();
  float uv_index = uv.index(mV); // valor de 1 a 233 
  float lux = lightMeter.readLightLevel();


  Serial.print(hum);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(mV);
  Serial.print(",");
  Serial.print(uv_index);
  Serial.print(",");
  Serial.println(lux);

  openLog.print(hum);
  delay(100);
  openLog.print(",");
  openLog.print(temp);
  delay(1000);

  openLog.print(",");
  openLog.print(mV);
  delay(1000);

  openLog.print(",");
  openLog.print(uv_index);
  delay(1000);

  openLog.print(",");
  openLog.println(lux);

  delay(1000);


}