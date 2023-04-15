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

RF24Interface::RF24Interface(){
    for (int i = 0; i <RF24_MaxCountTopics; i++){
        for (int j = 0; j < RF24_MaxCountSubscribers; j ++){
            subscribs[i][j] = nullptr;
        }
        subscribedTopics[i] = "\0";
    }
}

bool RF24Interface::loop(){
    if(Radio->isChipConnected()){   //если чип жив
        if(Radio->available()){     //смотрим есть ли данные
            //проводим обработку полученных данных. Это может быть только сообщение от сервера об изменении топика
            #ifdef WriteLog_SerialRF24
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

bool RF24Interface::subscribe(const char* topic){
    bool allOk = false;
    for (int i = 0; i < RF24_MaxCountTopics; i ++){ //ищем подписавшихся
        if (subscribedTopics[i] == topic){  //если уже есть кто-то подписавшийся на топик
            for (int j = 0; j < RF24_MaxCountSubscribers; j ++){    //смотрим есть ли пустое место для нового callback
                if (subscribs[i][j] == nullptr){    //если есть, то добавляем нового подписчика
                    subscribs[i][j] = callback;
                    allOk = true;
                }
            }
        } else if (subscribedTopics[i] == nullptr){ //если уже пошли пустые ячейки значит такая подписка первая
            subscribedTopics[i] = topic;
            subscribs[i][0] = callback;
            allOk = true;
            break;
        }
    }
    if (allOk){
        byte data[32];
        memcpy(data, topic, strlen(topic) + 1);
        data[strlen(topic) + 1] = 'd';
        Radio->stopListening();
        Radio->openWritingPipe(RF24_pipe);
        Radio->write(&data, 32);
        Radio->openReadingPipe(1, RF24_pipe);
        Radio->startListening();
    }
    return allOk;
}

bool RF24Interface::send(const char* topic, const char* data){
    if (strlen(topic) + strlen(data) < 30){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 's';
        memcpy(packet+strlen(topic)+2, data, strlen(data)+1);
        bool ans = false;
        Radio->stopListening();
        Radio->openWritingPipe(RF24_pipe);
        ans = Radio->write(&data, 32);
        Radio->openReadingPipe(1, RF24_pipe);
        Radio->startListening();
        return ans;
    }
    return false;
}

bool RF24Interface::send(const char* topic, int64_t data){
    if (strlen(topic) + sizeof(data) < 30){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 's';
        memcpy(packet+strlen(topic)+2, &data, sizeof(data)+1);
        bool ans = false;
        Radio->stopListening();
        Radio->openWritingPipe(RF24_pipe);
        ans = Radio->write(&data, 32);
        Radio->openReadingPipe(1, RF24_pipe);
        Radio->startListening();
        return ans;
    }
    return false;
}

bool RF24Interface::send(const char* topic, float data){
    if (strlen(topic) + sizeof(data) < 30){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 's';
        memcpy(packet+strlen(topic)+2, &data, sizeof(data)+1);
        bool ans = false;
        Radio->stopListening();
        Radio->openWritingPipe(RF24_pipe);
        ans = Radio->write(&data, 32);
        Radio->openReadingPipe(1, RF24_pipe);
        Radio->startListening();
        return ans;
    }
    return false;
}