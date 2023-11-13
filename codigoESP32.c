#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define SENSOR_PRESENCA 4

#define PHOTORESISTOR_PIN 34

#define LED_PIN 2

// MQTT defines
#define MQTT_BROKER "46.17.108.113"
#define MQTT_PORT 1883
#define MQTT_TOPIC_SUBSCRIBE "/TEF/lamp108/cmd"
#define MQTT_TOPIC_PUBLISH "/TEF/lamp108/attrs"
#define MQTT_TOPIC_PUBLISH_LUMINOSITY "/TEF/lamp108/attrs/luminosity"
#define MQTT_TOPIC_PUBLISH_LED "/TEF/lamp108/attrs/led"
#define MQTT_CLIENT_ID "fiware_108"
#define WIFI_SSID "FIAP-IBM"
#define WIFI_PASSWORD "Challenge@23!"

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(SENSOR_PRESENCA, INPUT);

  initWiFi();
  initMQTT();
}


void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  publishSensorData();
  client.loop();
}


void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}


void initMQTT() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
}


void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(MQTT_TOPIC_SUBSCRIBE);
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}


void publishSensorData() {
  int sensorValue = analogRead(PHOTORESISTOR_PIN);
  if (sensorValue > 110) {
    char msgBuffer[] = "Dia";
    client.publish(MQTT_TOPIC_PUBLISH_LUMINOSITY, msgBuffer);
  }
  else {
    char msgBuffer[] = "Noite";

    client.publish(MQTT_TOPIC_PUBLISH_LUMINOSITY, msgBuffer);
    int valor = digitalRead(SENSOR_PRESENCA);
    Serial.print("Estado sensor de presença: ");
    Serial.println(valor);
    if (valor == HIGH) {
        digitalWrite(LED_PIN, HIGH);
        char LedState[] = "LED_ON";
        client.publish(MQTT_TOPIC_PUBLISH_LED, LedState);
        delay(5000);
        digitalWrite(LED_PIN, LOW);
    }
    char LedState[] = "LED_OFF";
    client.publish(MQTT_TOPIC_PUBLISH_LED, LedState);
  }
}
