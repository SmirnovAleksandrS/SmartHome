#include "RF24_interface.h"


bool startRf24(RF24* radio){
    bool ans = false;
    ans = radio->begin();
    if(ans){
        
        radio->setDataRate(RF24_DataRate); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
        radio->setPALevel(RF24_PaLevel); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
        radio->setAutoAck(false);       // автоответ
        radio->setPayloadSize(32);
        uint8_t address[][6] = { "1Node", "2Node" };
        radio->openReadingPipe(1, address[0]);
        radio->openWritingPipe(address[1]);
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

            //вызов callback

            for (int i = 0; i < RF24_MaxCountTopics; i ++){
                if(subscribedTopics[i] == topicName){
                    for (int j = 0; j < RF24_MaxCountSubscribers; j ++){
                        if (subscribs[i][j] != nullptr){
                            subscribs[i][j]->callback(topicName, data, 32);
                        }else{
                            break;
                        }
                    }
                }
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
                    subscribs[i][j] = My_Sensor;
                    allOk = true;
                    break;
                }
            }
        } else if (subscribedTopics[i] == nullptr){ //если уже пошли пустые ячейки значит такая подписка первая
            subscribedTopics[i] = topic;
            subscribs[i][0] = My_Sensor;
            allOk = true;
            break;
        }
    }
    if (allOk){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 'd';
        Radio->stopListening();
        Radio->write(&packet, 32);
        Radio->startListening();
    }
    return allOk;
}

bool RF24Interface::send(const char* topic, const char* data){
    #ifdef WriteLog_SerialRF24
        Serial.println("Try send str");
    #endif

    if (strlen(topic) + strlen(data) < 30){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 's';
        memcpy(packet+strlen(topic)+2, data, strlen(data)+1);

        #ifdef WriteLog_SerialRF24
            Serial.print("Packet to send: ");
            for (int i = 0; i < 32; i ++){
                if (packet[i] == '\0'){
                    Serial.print("$");
                }else 
                    Serial.print((char)packet[i]);
            }
            Serial.println();
        #endif

        bool ans = false;
        Radio->stopListening();
        ans = Radio->write(&packet, 32);
        Radio->startListening();
        return ans;
    }
    return false;
}

bool RF24Interface::send(const char* topic, int64_t data){
    #ifdef WriteLog_SerialRF24
        Serial.println("Try send int64_t");
    #endif

    if (strlen(topic) + sizeof(data) < 30){
        byte packet[32];
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 'i';
        memcpy(packet+strlen(topic)+2, &data, sizeof(data)+1);

        #ifdef WriteLog_SerialRF24
            Serial.print("Packet to send: ");
            for (int i = 0; i < 32; i ++){
                if (packet[i] == '\0'){
                    Serial.print("$");
                }else 
                    Serial.print((char)packet[i]);
            }
            Serial.println();
        #endif

        bool ans = false;
        Radio->stopListening();
        ans = Radio->write(&packet, 32);
        Radio->startListening();
        return ans;
    }
    return false;
}

bool RF24Interface::send(const char* topic, float data){
    #ifdef WriteLog_SerialRF24
        Serial.println("Try send float");
    #endif

    if (strlen(topic) + sizeof(data) < 30){
        byte packet[32];
        for (int i =0; i < 32; i ++){
            packet[i] = '\0';
        }
        memcpy(packet, topic, strlen(topic) + 1);
        packet[strlen(topic) + 1] = 'f';
        memcpy(packet+strlen(topic)+2, &data, sizeof(data)+1);

        #ifdef WriteLog_SerialRF24
            Serial.print("Packet to send: ");
            for (int i = 0; i < 32; i ++){
                if (packet[i] == '\0'){
                    Serial.print("$");
                }else 
                    Serial.print((char)packet[i]);
            }
            Serial.println();
        #endif

        bool ans = false;
        Radio->stopListening();
        ans = Radio->write(&packet, 32);
        Radio->startListening();
        return ans;
    }
    return false;
}