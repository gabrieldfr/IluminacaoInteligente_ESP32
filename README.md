# Sistema de Iluminação Inteligente utilizando um servidor
> Status: Finalizado ✔️

## Responsável pelo projeto:
- Gabriel Rocha
- Linkedin: www.linkedin.com/in/gabrieldiegues

![ESP32_final_version](https://github.com/gabrieldfr/Sprint4_Edge/assets/127216244/9bc16561-8993-43ca-a3f5-58850d38b7ae)

# Projeto de Controle de Luminosidade e Sensor de Presença com MQTT

Este é um projeto de código aberto desenvolvido em um ESP32 para controlar a luminosidade de um ambiente com base em um sensor de luminosidade (fotorresistor) e acionar um LED com base em um sensor de presença. O projeto utiliza o protocolo MQTT para comunicação.

## Hardware Necessário

- ESP32
- Sensor de presença (PIR - Passive Infrared Sensor)
- Fotorresistor (Sensor de Luminosidade)
- LED
- Resistores
- Conexão com a Internet (via módulo WiFi)

## Dependências

- [Arduino.h](https://www.arduino.cc/reference/pt/)
- [WiFi.h](https://www.arduino.cc/en/Reference/WiFi)
- [PubSubClient.h](https://pubsubclient.knolleary.net/)

## Configuração

Antes de carregar o código no Arduino, certifique-se de ajustar as seguintes configurações no código:

```cpp
#define SENSOR_PRESENCA 4
#define PHOTORESISTOR_PIN 34
#define LED_PIN 2

// Configurações MQTT
#define MQTT_BROKER "46.17.108.113"
#define MQTT_PORT 1883
#define MQTT_TOPIC_SUBSCRIBE "/TEF/lamp108/cmd"
#define MQTT_TOPIC_PUBLISH "/TEF/lamp108/attrs"
#define MQTT_TOPIC_PUBLISH_LUMINOSITY "/TEF/lamp108/attrs/luminosity"
#define MQTT_TOPIC_PUBLISH_LED "/TEF/lamp108/attrs/led"
#define MQTT_CLIENT_ID "fiware_108"
#define WIFI_SSID "FIAP-IBM"
#define WIFI_PASSWORD "Challenge@23!"
```

- `SENSOR_PRESENCA`: Pino de entrada do sensor de presença.
- `PHOTORESISTOR_PIN`: Pino de entrada do fotorresistor.
- `LED_PIN`: Pino de saída para o LED.

Configure também as informações de conexão WiFi e MQTT de acordo com sua rede.

## Funções Principais

- `initWiFi()`: Inicializa a conexão WiFi.
- `initMQTT()`: Inicializa a conexão MQTT.
- `reconnectMQTT()`: Reconecta ao servidor MQTT em caso de desconexão.
- `publishSensorData()`: Realiza a leitura dos sensores, publica os dados no servidor MQTT e controla o estado do LED com base nas condições de luminosidade e detecção de presença.

## Uso

Após carregar o código no ESP32, o dispositivo enviará informações sobre a luminosidade e o estado do LED para o servidor especificado. Os tópicos MQTT utilizados estão configurados nas constantes `MQTT_TOPIC_PUBLISH_LUMINOSITY` e `MQTT_TOPIC_PUBLISH_LED`.

## Link de acsso para o nosso pitch do projeto:
https://youtu.be/J_aqqTu-79g?si=vd4uX370-4J_wUy9

