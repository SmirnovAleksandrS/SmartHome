/*
Победа над nRF24L01: на три шага ближе, передатчик
https://habr.com/ru/post/476716/
*/

#include <SPI.h>
#include <RF24.h>
#include "Sensor_DHT11.h"
#include "RF24_interface.h"

//////////////////////////Создаем интерфейс//////////////////////////////

RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
String* RF24Interface::subscribedTopics = new String [RF24_MaxCountTopics];
TypeOfCallback RF24Interface::subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];
RF24Interface rf24_inter = RF24Interface();

////////////////////////Создаем сенсоры//////////////////////////////////

DHT_Unified dht_unif = DHT_Unified(5, DHT11);
Sensor_DHT11 dht11(&rf24_inter, &dht_unif);

///////////////////////Основной код//////////////////////////////////////

void setup() {
  startRf24(&radio);
}

void loop() {
}