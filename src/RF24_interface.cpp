#include "RF24_interface.h"

bool startRf24(RF24* radio){
    bool ans = false;
    ans = radio->begin();
    if(ans){
        radio->setDataRate(RF24_DataRate); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
        // radio->setCRCLength(RF24_CRC_8); // размер контрольной суммы 8 bit или 16 bit
        radio->setPALevel(RF24_PaLevel); // уровень питания усилителя RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
        radio->setChannel(RF24_Channel);         // установка канала
        radio->setAutoAck(false);       // автоответ
        radio->powerUp();    // включение или пониженное потребление powerDown - powerUp
        radio->openReadingPipe(1, RF24_pipe);
        radio->startListening();
    }
    return ans;          
}

bool RF24_callback(char* topic, byte* message, unsigned int length){
    return 1;
}

RF24Senosr::RF24Senosr(Interface* inter, RF24* radio): Inter(inter), Radio(radio){}

bool RF24Senosr::iteration(){
    if(Radio->isChipConnected()){
        if(Radio->available()){
            Serial.print("Receved: ");
            byte data[32];
            Radio->read(data, 32);
            int topicLn = 0;
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
            char type = (char)data[topicLn+1];
            Serial.print(topicLn);
            Serial.print(' ');
            Serial.print(type);
            Serial.print(' ');
            Serial.print(topicName);
            Serial.print(' ');
            switch (type)
            {
            case 'i':
                int value;
                memcpy(&value, data +topicLn + 2, sizeof(int));
                Serial.println(value);
                break;
            }
        }
        return true;
    }
    return false;
}