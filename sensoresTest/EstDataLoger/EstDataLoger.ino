/*
recepticón de datos a data logger
*/

#include <Adafruit_Sensor.h>
#include <DHT.h>  
#include <TimeLib.h>


#define ledTestigo 2

#define DHTPIN221 4     // def como agregadi 221, a mi DHT 22, asignado con valor 1
#define DHTTYPE221 DHT22


DHT dht221(DHTPIN221, DHTTYPE221);

struct valDHT {
  float temp;
  float hum;
  int second;
  int minute;
  int hour;
  int day;
  int week;
  int month;
  int year;
}; 


void setup() {
  pinMode(ledTestigo, OUTPUT);

  Serial.begin(9600);
  Serial.println();
  Serial.println("Starting DHT22");
  dht221.begin();
  Serial.println("time mark");
  //setTime(hr,min,sec,day,month,yr);
  setTime(00,00,00,10,10,2026);
  time_t t = now();
  int h = hour(t);
  int d = day(t);

  Serial.println(h);
  Serial.println(d);

}

void loop() {
  valDHT data; 
  float DHT221hum = dht221.readHumidity();
  float DHT221temp = dht221.readTemperature();

  digitalWrite(ledTestigo, HIGH);
  data = {DHT221temp, DHT221hum, second(), minute(), hour(), day(), month(), year()};
  delay(100);
  digitalWrite(ledTestigo, LOW);
  delay(1000)

  




}
