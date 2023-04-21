// #include <SPI.h>
// #include <RF24.h>
#include "Sensor_DHT11.h"
#include "RF24_interface.h"
#include "Sensor_LED.h"
#include "Sensor_oled.h"
// #include "Sensor_oled_two.h"
// #include "Sensor_led_pwm.h"
#include "Sensor_potentiometr.h"
// #include "OLED_I2C.h"
// #include "Sensor_serva.h"
// #include "Sensor_7disp.h"
#include <GyverOLED.h>
// //////////////////////////Создаем интерфейс RF24//////////////////////////////

RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
String* RF24Interface::subscribedTopics = new String [RF24_MaxCountTopics];
typeSensor RF24Interface::subscribs[RF24_MaxCountTopics][RF24_MaxCountSubscribers];




// ////////////////////////Создаем сенсоры//////////////////////////////////

// //Создаем DHT
// DHT_Unified dht_unif = DHT_Unified(2, DHT11);
// Sensor_DHT11 dht11(&dht_unif, "temp", "humb");
// RF24Interface rf24_inter_dht11 = RF24Interface(&dht11);

// //создаем LED
Sensor_LED LED = Sensor_LED(5);
RF24Interface LED_inter = RF24Interface(&LED);

// создаем led pwm
// Sensor_led_pwm led_pwm = Sensor_led_pwm(5);
// RF24Interface led_pwm_inter = RF24Interface(&led_pwm);

// создаем oled
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
Sensor_oled oleddd = Sensor_oled(&oled, "humb", "temp", "resist");
RF24Interface oled_inter = RF24Interface(&oleddd);


// OLED myOLED = OLED(18, 19, 8);
// OLED myOLED(SDA, SCL, 8); 

// ///////////////////////Основной код//////////////////////////////////////

// // подключаем шрифты для текста и цифр
// extern uint8_t TinyFont[];
// extern uint8_t SmallFont[];
// extern uint8_t MediumNumbers[];
// extern uint8_t BigNumbers[];

// uint64_t timer1;

void setup(){
  Serial.begin(9600);
  Serial.print(startRf24(&radio));

  oleddd.setInterface(&oled_inter);
  oleddd.init();
  // oled.clear();
  // oled.setScale(1);
  // oled.setCursorXY(0, 5);
  // oled.print("Humudity: ");
  // oled.setCursorXY(0, 26);
  // oled.print("Tempature: ");
  // oled.setCursorXY(0, 47);
  // oled.print("Volthuiage: ");
  // oled.update();
  // Serial.print(4);

  LED.setInterface(&LED_inter);
  LED_inter.subscribe("LED_nano");

  // dht11.setInterface(&rf24_inter_dht11);
  // timer1 = millis();
 
}

void loop(){
  LED.iteration();
  oleddd.iteration();
}