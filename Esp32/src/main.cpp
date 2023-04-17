#include <Arduino.h>
#include <MQTT_interface.h>

#include "RF24_sensor.h"
#include "Sensor_LED.h"
#include "Sensor_PWM_LED.h"
///////////////////////////////Инициализация MQTT интерфейса///////////////////////////////////////

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<bool(*)(char* topic, byte* message, unsigned int length)>> MQTTInterface::subscribs;

///////////////////////////////Создание callback'оф для датчиков/////////////////////////////////////

// bool DHT_callback(char* topic, byte* message, unsigned int length){
//   Serial.println("Huyse rabotaet!");
//   return true;
// }

////////////////////////////////Инициализация nrf24l01 как датчика///////////////////////////////////

RF24 radio(4, 5);
MQTTInterface TxRxInterface = MQTTInterface("Arduino1", &RF24Senosr::RF24_callback);

RF24* RF24Senosr::Radio = &radio;
Interface* RF24Senosr::Inter = &TxRxInterface;

RF24Senosr rf24 = RF24Senosr();

////////////////////////////////Создание интерфейсов для датчиков///////////////////////////////

MQTTInterface LED_inter = MQTTInterface("LED", &Sensor_LED::LED_Callback);   //создание экземпляров интерфейса

////////////////////////////////Создание датчиков////////////////////////////////////////////////////

uint8_t Sensor_LED::PIN;
Sensor_LED LED1 = Sensor_LED(&LED_inter, 1);

// uint8_t Sensor_PWM_LED::PIN;
// Sensor_PWM_LED LED2 = Sensor_PWM_LED(&LED_inter, 1);

///////////////////////////////Основной код////////////////////////////////////////////////////////

void setup() {
  startMQTT(&client);
  startRf24(&radio);  
  LED_inter.subscribe("LED_Test");
}

void loop() {
  rf24.iteration();
  LED1.iteration();
}