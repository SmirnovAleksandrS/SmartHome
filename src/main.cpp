#include <Arduino.h>
#include <MQTT_connect.h>

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<bool(*)(const char*)>> MQTTInterface::subscribs;

MQTTInterface interf1("TestInter");
MQTTInterface interf2("TestInter2");

bool callback1(const char*){
  Serial.println("Huyse rabotaet!");
  return true;
}

bool callback2(const char*){
  Serial.println("Huyse rabotaet2!");
  return true;
}

void setup() {
  start(&client);
  // client.subscribe("esp32/input");
  interf1.setCallback(&callback1);
  interf2.setCallback(&callback2);

  interf1.subscribe("esp32/output");
  interf2.subscribe("esp32/output");
  interf2.subscribe("esp32/input");

}

void loop() {
  if (client.connected()){
    client.loop();
    interf1.send("Test", "0");
    delay(5000);
  } else {
    Serial.print(client.connect(MQTT_clientId, MQTT_login, MQTT_passwd));
    Serial.print(client.state());
    Serial.println(client.publish("esp32/output", "3"));
  }
  

}