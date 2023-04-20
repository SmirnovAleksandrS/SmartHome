#include <SPI.h>
#include <RF24.h>
// #include "Sensor_DHT11.h"
#include "RF24_interface.h"
#include "Sensor_LED.h"
//////////////////////////Создаем интерфейс RF24//////////////////////////////

RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
String* RF24Interface::subscribedTopics = new String [RF24_MaxCountTopics];
typeSensor RF24Interface::subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];


////////////////////////Создаем сенсоры//////////////////////////////////

// DHT_Unified dht_unif = DHT_Unified(5, DHT11);
// Sensor_DHT11 dht11(&dht_unif);
// RF24Interface rf24_inter_dht11 = RF24Interface();

Sensor_LED LED = Sensor_LED(5);

RF24Interface LED_inter = RF24Interface(&LED);

///////////////////////Основной код//////////////////////////////////////

void setup() {
  Serial.begin(9600);
  Serial.print(1);
  startRf24(&radio);
  LED.setInterface(&LED_inter);
  
  Serial.println(1);
  // dht11.setInterface(&rf24_inter_dht11);
}

void loop() {
  // Serial.println(dht11.iteration());
  // 
  LED.iteration();
  LED_inter.subscribe("LED");
}