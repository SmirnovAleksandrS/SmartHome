#include <Arduino.h>

#include <MQTT_interface.h>
#include "RF24_sensor.h"

#include "Sensor_LED.h"
#include "Sensor_led_pwm.h"
#include "Sensor_potentiometr.h"

#include "esp32-hal-ledc.h"

///////////////////////////////Инициализация MQTT интерфейса///////////////////////////////////////

WiFiClient espClient;       //класс для взаимодействия с Wi-Fi
PubSubClient client(espClient); //интерфейс для MQTT

PubSubClient* MQTTInterface::PSClient = &client;  //Инициализация статического поля всех интерфейсных классов MQTTInterface
std::forward_list<std::string> MQTTInterface::subscribedTopics;
std::forward_list<std::forward_list<Sensor*>> MQTTInterface::subscribs;

////////////////////////////////Инициализация nrf24l01 как датчика///////////////////////////////////

RF24 radio(4, 5);
RF24* RF24Senosr::Radio = &radio;
RF24Senosr rf24 = RF24Senosr();

MQTTInterface TxRxInterface = MQTTInterface("Nano", &rf24);

////////////////////////////////Создание датчиков////////////////////////////////////////////////////

Sensor_led_pwm Led_pwm = Sensor_led_pwm(16);
Sensor_potentiometr potent(32, "Resistance");

////////////////////////////////Создание интерфейсов для датчиков///////////////////////////////

MQTTInterface Led_pwm_inter = MQTTInterface("LED1", &Led_pwm);   //создание экземпляров интерфейса
MQTTInterface Potent_inter = MQTTInterface("Pot", &potent);

///////////////////////////////Основной код////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  // pinMode(16, OUTPUT);
  // ledcSetup(LedChannel, Frequency, Resolution);                                    
  // ledcAttachPin(16, LedChannel);
  // ledcWrite(LedChannel, 253);
  // delay(100);
  // ledcWrite(LedChannel, 0);

  //инициализируем интерфейсы связи
  startMQTT(&client);
  startRf24(&radio);  
  rf24.setInterface(&TxRxInterface);

  Led_pwm.setInterface(&Led_pwm_inter);
  Led_pwm_inter.subscribe("room1/Pot/Resistance");

  potent.setInterface(&Potent_inter);
}

void loop() {
  rf24.iteration();
  potent.iteration();
  Led_pwm.iteration();
}
