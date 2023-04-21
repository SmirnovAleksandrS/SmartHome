#include <SPI.h>
#include <RF24.h>
#include "Sensor_DHT11.h"
#include "RF24_interface.h"
#include "Sensor_LED.h"
#include "Sensor_oled.h"
#include "Sensor_led_pwm.h"
#include "Sensor_potentiometr.h"
// #include "Sensor_serva.h"
// #include "Sensor_7disp.h"
//////////////////////////Создаем интерфейс RF24//////////////////////////////

RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
String* RF24Interface::subscribedTopics = new String [RF24_MaxCountTopics];
typeSensor RF24Interface::subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];


////////////////////////Создаем сенсоры//////////////////////////////////

//Создаем DHT
DHT_Unified dht_unif = DHT_Unified(8, DHT11);
Sensor_DHT11 dht11(&dht_unif, "temp", "humb");
RF24Interface rf24_inter_dht11 = RF24Interface(&dht11);

//создаем LED
// Sensor_LED LED = Sensor_LED(7);
// RF24Interface LED_inter = RF24Interface(&LED);

//создаем led pwm
Sensor_led_pwm led_pwm = Sensor_led_pwm(7);
RF24Interface led_pwm_inter = RF24Interface(&led_pwm);

// создаем oled
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oleddd;
Sensor_oled oled = Sensor_oled(&oleddd, "humb", "temp", "resist");
RF24Interface oled_inter = RF24Interface(&oled);


///////////////////////Основной код//////////////////////////////////////

void setup() {
  Serial.begin(9600);
  startRf24(&radio);

  // LED.setInterface(&LED_inter);
  // LED_inter.subscribe("LED_nano");

  dht11.setInterface(&rf24_inter_dht11);

  oled.setInterface(&oled_inter);
  oled_inter.subscribe("hump");
  oled_inter.subscribe("temp");
  oled_inter.subscribe("resist");

  led_pwm.setInterface(&led_pwm_inter);
}

void loop() {
  // Serial.println(dht11.iteration());
  dht11.iteration();
  // 
  // LED.iteration();
  led_pwm.iteration();
  oled.iteration();
}