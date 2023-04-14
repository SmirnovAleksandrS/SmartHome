#include "RF24_interface.h"


bool startRf24(RF24* radio){
    bool ans = false;
    ans = radio->begin();
    if(ans){
        radio->setDataRate(RF24_DataRate); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
        radio->setPALevel(RF24_PaLevel); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
        radio->setChannel(RF24_Channel);         // установка канала
        radio->setAutoAck(false);       // автоответ
        radio->powerUp();    // включение или пониженное потребление powerDown - powerUp
        radio->openReadingPipe(1, RF24_pipe);
        radio->startListening();
    }
    return ans;          
}

////////////////////////////блок для RF24Interface////////////////////////////////

bool RF24Interface::loop(){
    if(Radio->isChipConnected()){   //если чип жив
        if(Radio->available()){     //смотрим есть ли данные
            //проводим обработку полученных данных. Это может быть только сообщение от сервера об изменении топика
            #ifdef WriteLog_Serial
                Serial.print("Receved: ");
            #endif
            //получаем пакет
            byte data[32];
            Radio->read(data, 32);
            int topicLn = 0;

            //отпарсиваем название топика
            for (int i = 0;i < 32; i ++){
                if(data[i] == '\0'){
                    topicLn = i;
                    break;
                }
            }
            char* topicName = new char [topicLn+1];
            for (int i = 0; i < topicLn; i ++){
                topicName[i] = (char)data[i];
            }
            topicName[topicLn] = '\0';

            //отпарсиваем полученные данные
            byte* values = new byte [32 - topicLn];
            for(int i = topicLn + 1; i < 32; i ++){
                values[i-topicLn - 1] = data[i];
            }
        }
        return true;
    }
    return false;
}