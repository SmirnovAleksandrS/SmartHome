// #include <SPI.h>
// #include <RF24.h>
#include "Sensor_DHT11.h"
#include "RF24_interface.h"
#include "Sensor_LED.h"
// #include "Sensor_oled.h"
// #include "Sensor_oled_two.h"
// #include "Sensor_led_pwm.h"
#include "Sensor_potentiometr.h"
#include "OLED_I2C.h"
// #include "Sensor_serva.h"
// #include "Sensor_7disp.h"
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
Sensor_LED LED = Sensor_LED(7);
RF24Interface LED_inter = RF24Interface(&LED);

// создаем led pwm
// Sensor_led_pwm led_pwm = Sensor_led_pwm(5);
// RF24Interface led_pwm_inter = RF24Interface(&led_pwm);

// // создаем oled
// // GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oleddd;
// // Sensor_oled oled = Sensor_oled(&oleddd, "humb", "temp", "resist");
// // RF24Interface oled_inter = RF24Interface(&oled);

// // создаем oled_two
// Sensor_oled_two oled_two = Sensor_oled_two("humb", "temp", "resist");
// RF24Interface oled_inter_two = RF24Interface(&oled_two);

// OLED myOLED = OLED(18, 19, 8);
OLED myOLED(SDA, SCL, 8); 

// ///////////////////////Основной код//////////////////////////////////////

// void setup() {
//   Serial.begin(9600);
//   Serial.print(startRf24(&radio));
//   oled.begin();
//   oled.setFont(TinyFont);
//   oled.print("aaaaaaaaaaa", CENTER, 10);
//   oled.update();
//   // oled_two.begin();
//   // LED.setInterface(&LED_inter);
//   // LED_inter.subscribe("LED_nano");

//   // dht11.setInterface(&rf24_inter_dht11);

//   // oled_two.setInterface(&oled_inter_two);
//   // oled_inter_two.subscribe("hump");
//   // oled_inter_two.subscribe("temp");
//   // oled_inter_two.subscribe("resist");
// }


          // подключаем библиотеку для экрана  // создаем объект myOLED

// подключаем шрифты для текста и цифр
extern uint8_t TinyFont[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

uint64_t timer1;

void setup(){
  Serial.begin(9600);
  Serial.print(startRf24(&radio));
  myOLED.begin();  // инициализируем экран

  LED.setInterface(&LED_inter);
  LED_inter.subscribe("LED_nano");

  // dht11.setInterface(&rf24_inter_dht11);
  timer1 = millis();
  

  // led_pwm.setInterface(&led_pwm_inter);

  // oled_two.setInterface(&oled_inter_two);
  // oled_inter_two.subscribe("hump");
  // oled_inter_two.subscribe("temp");
  // oled_inter_two.subscribe("resist");
  //    myOLED.setFont(TinyFont);
  //  myOLED.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LEFT, 10);
  //  myOLED.update();
 
  //  // выводим текст по центру экрана

  // myOLED.setFont(TinyFont);
  // myOLED.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LEFT, 10);
  // myOLED.update();
 
}

void loop(){
  // Serial.println(dht11.iteration());
  // dht11.iteration();
  // 
  LED.iteration();
  // led_pwm.iteration();
  // oled.iteration();
  // oled_two.iteration();   

  // выводим текст по левому краю экрана

  if(millis() - timer1 > 5000){
    // myOLED.setFont(TinyFont);
    // myOLED.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LEFT, 10);
    // myOLED.update();
    Serial.println("t");
    timer1 = millis();
  

  // // выводим текст по центру экрана
  myOLED.setFont(SmallFont);
  myOLED.print("ABCDEFG", CENTER, 25);
  myOLED.update();

  myOLED.clrScr(); // очищаем экран от надписей
  myOLED.update();
  myOLED.invert(true); // включаем инверсию экрана

  // выводим цифры по правому краю экрана
  myOLED.setFont(MediumNumbers);
  myOLED.print("123456789", RIGHT, 5);
  myOLED.update();

  // выводим цифры, начиная с 5 пикселя строки
  // myOLED.setFont(BigNumbers);
  // myOLED.print("123456789", 5, 30);
  // myOLED.update();

  // myOLED.clrScr(); // очищаем экран от надписей
  // myOLED.update();
  // myOLED.invert(false); // отключаем инверсию экрана
  }

}