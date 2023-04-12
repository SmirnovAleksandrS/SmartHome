#include <Arduino.h>
#include <MQTT_interface.h>
#include <RF24_interface.h>
#include <Sensor_DHT11.h>
///////////////////////////////Инициализация MQTT интерфейса///////////////////////////////////////

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<bool(*)(char* topic, byte* message, unsigned int length)>> MQTTInterface::subscribs;

///////////////////////////////Создание callback'оф для датчиков/////////////////////////////////////

bool DHT_callback(char* topic, byte* message, unsigned int length){
  Serial.println("Huyse rabotaet!");
  return true;
}

////////////////////////////////Создание самих интерфейсов для датчиков///////////////////////////////

MQTTInterface interf1 = MQTTInterface("TestInter", &DHT_callback);   //создание экземпляров интерфейса

////////////////////////////////Инициализация nrf24l01 как датчика///////////////////////////////////

RF24 radio(4, 5);
MQTTInterface TxRxInterface = MQTTInterface("Arduino1", &RF24Senosr::RF24_callback);

RF24* RF24Senosr::Radio = &radio;
Interface* RF24Senosr::Inter = &TxRxInterface;

RF24Senosr rf24 = RF24Senosr();


////////////////////////////////Создание датчиков////////////////////////////////////////////////////

Sensor_DHT11 dht (&interf1);

///////////////////////////////Основной код////////////////////////////////////////////////////////

void setup() {
  startMQTT(&client);
  startRf24(&radio);
  // interf1.subscribe("esp32/output");
  // interf2.subscribe("esp32/output");
  // interf2.subscribe("esp32/input");
  
}

void loop() {
  rf24.iteration();
  dht.iteration();
}