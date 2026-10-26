
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <time.h>

// -------------------- Sensor --------------------
#define DHTPIN221 4
#define DHTTYPE221 DHT22

DHT dht221(DHTPIN221, DHTTYPE221);

// -------------------- Wi-Fi --------------------
const char* ssid = "ESP8266";
const char* password = "thereisaspoon";

// IP DE EJEMPLO: debe ser la IP de Ubuntu en la red del ESP8266
const char* mqtt_server = "192.168.4.2";

// -------------------- MQTT --------------------
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
const unsigned long interval = 10000;

#define MSG_BUFFER_SIZE 200
char msg[MSG_BUFFER_SIZE];
char timeString[30];

int value = 0;
const int ledTestigo = 2;

// -------------------- Configuración --------------------
void setup() {
  Serial.begin(115200);

  pinMode(ledTestigo, OUTPUT);
  digitalWrite(ledTestigo, HIGH);

  dht221.begin();

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // NTP requiere acceso a un servidor horario.
  // Si la red del ESP8266 no tiene acceso a Internet,
  // la hora no se sincronizará automáticamente.
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
}

// -------------------- Bucle principal --------------------
void loop() {
  if (WiFi.softAPgetStationNum() == 0) {
    digitalWrite(ledTestigo, LOW);
  }

  if (!client.connected()) {
    digitalWrite(ledTestigo, LOW);
    reconnect();
  }

  client.loop();

  unsigned long now = millis();

  if (now - lastMsg >= interval) {
    lastMsg = now;

    float hum = dht221.readHumidity();
    float temp = dht221.readTemperature();

    if (isnan(hum) || isnan(temp)) {
      Serial.println("Error leyendo el DHT22");
      return;
    }

    // Obtener la hora local si el reloj está sincronizado.
    time_t epoch = time(nullptr);
    struct tm timeinfo;

    if (epoch > 1700000000 &&
        localtime_r(&epoch, &timeinfo) != nullptr) {

      strftime(timeString, sizeof(timeString),
               "%Y-%m-%d %H:%M:%S", &timeinfo);

    } else {
      snprintf(timeString, sizeof(timeString),
               "time_not_synced");
    }

    snprintf(msg, sizeof(msg),
             "{\"time\":\"%s\",\"temp\":%.2f,\"hum\":%.2f}",
             timeString, temp, hum);

    if (client.connected()) {
      bool sent = client.publish("est1/data", msg);

      if (sent) {
        Serial.print("Publicado: ");
        Serial.println(msg);
      } else {
        Serial.println("Error al publicar por MQTT");
      }
    }

    value++;
  }

  if (client.connected()) {
    digitalWrite(ledTestigo, LOW);
  }
}

// -------------------- Punto de acceso Wi-Fi --------------------
void setup_wifi() {
  Serial.println();
  Serial.println("Iniciando punto de acceso Wi-Fi");

  WiFi.mode(WIFI_AP);

  if (WiFi.softAP(ssid, password)) {
    Serial.print("Red creada: ");
    Serial.println(ssid);

    Serial.print("IP del ESP8266: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Error creando el punto de acceso");
  }

  randomSeed(micros());
}

// -------------------- Recepción MQTT --------------------
void callback(char* topic, byte* payload,
              unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("]: ");

  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

// -------------------- Reconexión MQTT --------------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conexión MQTT... ");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
    } else {
      Serial.print("falló, estado MQTT = ");
      Serial.println(client.state());
      delay(5000);
    }
  }
}
