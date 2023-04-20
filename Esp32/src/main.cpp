#include <Arduino.h>
#include <MQTT_interface.h>

#include "RF24_sensor.h"
#include "Sensor_LED.h"
// #include "Sensor_PWM_LED.h"
///////////////////////////////Инициализация MQTT интерфейса///////////////////////////////////////

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<Sensor*>> MQTTInterface::subscribs;

////////////////////////////////Инициализация nrf24l01 как датчика///////////////////////////////////

RF24 radio(4, 5);
RF24* RF24Senosr::Radio = &radio;
// Interface* RF24Senosr::Inter = &TxRxInterface;
RF24Senosr rf24 = RF24Senosr();

MQTTInterface TxRxInterface = MQTTInterface("Arduino1", &rf24);

////////////////////////////////Создание датчиков////////////////////////////////////////////////////

Sensor_LED LED1 = Sensor_LED(22);
Sensor_LED LED2 = Sensor_LED(15);

////////////////////////////////Создание интерфейсов для датчиков///////////////////////////////

MQTTInterface LED_inter1 = MQTTInterface("LED1", &LED1);   //создание экземпляров интерфейса
MQTTInterface LED_inter2 = MQTTInterface("LED2", &LED2);   //создание экземпляров интерфейса

///////////////////////////////Основной код////////////////////////////////////////////////////////

void setup() {
  startMQTT(&client);
  startRf24(&radio);  
  rf24.setInterface(&TxRxInterface);
  LED1.setInterface(&LED_inter1);
  LED2.setInterface(&LED_inter2);
  // client.subscribe("Test");
  LED_inter1.subscribe("led1");
  // LED_inter2.subscribe("LED2");
  // TxRxInterface.subscribe("LED");
}

void loop() {
  // LED_inter.send("LED", "data");
  // delay(1000);
  // Serial.println(rf24.iteration());
  rf24.iteration();
  LED1.iteration();
  // LED2.iteration();
}