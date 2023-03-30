#include <Arduino.h>
#include <MQTT_connect.h>
#include <Sensors_interface.h>

///////////////////////////////////////////////////////////////////////////////////////////////

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<bool(*)(char* topic, byte* message, unsigned int length)>> MQTTInterface::subscribs;

///////////////////////////////////////////////////////////////////////////////////////////////

bool callback1(char* topic, byte* message, unsigned int length){
  Serial.println("Huyse rabotaet!");
  return true;
}

bool callback2(char* topic, byte* message, unsigned int length){
  Serial.println("Huyse rabotaet2!");
  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////

MQTTInterface interf1("TestInter", &callback1);   //создание экземпляров интерфейса
MQTTInterface interf2("TestInter2", &callback2);

///////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  start(&client);
  interf1.subscribe("esp32/output");
  interf2.subscribe("esp32/output");
  interf2.subscribe("esp32/input");
}

void loop() {

}