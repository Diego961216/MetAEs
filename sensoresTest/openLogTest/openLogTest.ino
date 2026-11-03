#include <SoftwareSerial.h>

// RX de Arduino = pin 10
// TX de Arduino = pin 11
SoftwareSerial openLog(10, 11);

void setup() {
  Serial.begin(9600);
  openLog.begin(9600);

  Serial.println("Arduino listo.");
  Serial.println("Escribe un mensaje y presiona Enviar.");
}

void loop() {
  if (Serial.available() > 0) {
    String mensaje = Serial.readStringUntil('\n');
    mensaje.trim();

    if (mensaje.length() > 0) {
      openLog.println(mensaje);

      Serial.print("Mensaje enviado al OpenLog: ");
      Serial.println(mensaje);
    }
  }
}