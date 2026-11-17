#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_BMP280.h>

#define SDA_PIN 21
#define SCL_PIN 22
#define BMP_ADDR 0x76   // Cambia a 0x77 si no se detecta

const float SEA_LEVEL_HPA = 1013.25; // Ajusta con la presión local a nivel del mar

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 3000);

  Wire.begin(SDA_PIN, SCL_PIN);
  
  if (!aht.begin()) {
    Serial.println("Error: no se detecta el AHT20.");
    while (1) delay(1000);
  }
  Serial.println("AHT20 inicializado.");

  if (!bmp.begin(BMP_ADDR)) {
    Serial.println("Error: no se detecta el BMP280.");
    while (1) delay(1000);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  Serial.println("BMP280 inicializado.");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(SEA_LEVEL_HPA);
  float tempBmp  = bmp.readTemperature();

  if (isnan(temp.temperature) || isnan(pressure)) {
    Serial.println("Lectura inválida, reintentando...");
    delay(2000);
    return;
  }

  Serial.printf("AHT20  -> Temp: %.2f °C | Humedad: %.1f %%\n",
                temp.temperature, humidity.relative_humidity);
  Serial.printf("BMP280 -> Temp: %.2f °C | Presión: %.2f hPa | Altitud: %.1f m\n",
                tempBmp, pressure, altitude);
  Serial.println("---");

  delay(2000);
}