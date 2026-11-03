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

*/

// #include <time.h> solve time with RTC


#include <Wire.h>

#include <DHT.h>
#include <GUVA-S12SD.h>
#include <BH1750.h>

#define DHTPIN221 4
#define DHTTYPE221 DHT22

DHT dht221(DHTPIN221, DHTTYPE221);

GUVAS12SD uv(A0);
BH1750 lightMeter;

void setup(){
  Serial.begin(9600);
  Wire.begin();

  dht221.begin();
  lightMeter.begin();

}

void loop(){

  float hum = dht221.readHumidity();
  float temp = dht221.readTemperature();
  
  float mV = uv.read();
  float uv_index = uv.index(mV); // valor de 1 a 233 
  float vl = lightMeter.readLigtLevel();


  Serial.print(hum);
  Serial.print(temp);
  Serial.print(mV);
  Serial.print(uv_index);
  Serial.print(vl);
  Serial.println();
}