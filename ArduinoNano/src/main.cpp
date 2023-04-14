/*
Победа над nRF24L01: на три шага ближе, передатчик
https://habr.com/ru/post/476716/
*/

#include <SPI.h>
#include <RF24.h>
#include "RF24_interface.h"


RF24 radio(9, 10); // порты D9, D10: CSN CE
RF24* RF24Interface::Radio = &radio;
RF24Interface inter1();

// const uint32_t pipe = 0x7878787878; // адрес рабочей трубы;
// int64_t iteration = 0;
// const char str[] = "strln";

void setup() {
  startRf24(&radio);
  // Serial.begin(115200);
  // Serial.println("TransmitterTester ON");

  // radio.begin();                // инициализация
  // delay(2000);
  // radio.setDataRate(RF24_1MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  // // radio.setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
  // radio.setPALevel(RF24_PA_MAX); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  // radio.setChannel(0x6f);         // установка канала
  // radio.setAutoAck(false);       // автоответ
  // radio.powerUp();               // включение или пониженное потребление powerDown - powerUp
  // radio.stopListening();  //радиоэфир не слушаем, только передача
  // radio.openWritingPipe(0x7878787878);   // открыть трубу на отправку
}

void loop() {
  // byte data[32];
  // memcpy(data, str, strlen(str)+1);
  // data[strlen(str)+1] = 's';
  // // memcpy(data+strlen(str)+2, &iteration, sizeof(iteration));
  // char my_str[] = "asdfg";
  // memcpy(data+strlen(str)+2, &my_str, strlen(my_str)+1);
  // radio.write(&data, 32);
  // for (int i = 0; i < 32; i ++)
  //   Serial.print((char)data[i]);
  // Serial.println();
  // iteration++;
  // delay(100);
  // // Serial.println("data= " + String(data));
  // RF24Interface::loop();
}