#include "RF24_sensor.h"


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

////////////////////////////блок для RF24Sensor//////////////////////////////// 

RF24Senosr::RF24Senosr(){}

bool RF24Senosr::RF24_callback(char* topic, byte* message, unsigned int length){
    //byte массив по-факту массив char, т.к. ничего другого запихать туда нельзя.
    //шаг первый, распарсим что это за данные, строка или число, т.к. число в строковом виде занимает больше места
    char type_message = 'i';
    for(int i = 0; i < length; i ++){
        if (!(('0' <= message[i] && message[i] <= '9') || (message[i] == '.')) && type_message){
            type_message = 's';
        }else if(message[i] == '.'){
            type_message = 'f';
        }
    }
    //шаг второй парсим строку нужным методом
    bool correctLen = true;
    byte data[32];
    memcpy(data, topic, strlen(topic)+1);
    char* message_str = reinterpret_cast<char*>(message);
    int64_t data_int;
    float data_float;
    switch (type_message){
        case 'i':
            data_int = atoi(message_str);
            if(sizeof(data_int) + strlen(topic) < 32)
                memcpy(data+strlen(topic)+2, &data_int, sizeof(data_int));
            else
                correctLen = false;
            break;
        case 's':
            if(strlen(message_str) + strlen(topic) < 31)
                memcpy(data+strlen(topic)+2, message_str, strlen(message_str)+1);
            else
                correctLen = false;
            break;
        case 'f':
            data_float = atof(message_str);
            if(sizeof(data_float) + strlen(topic) < 32)
                memcpy(data+strlen(topic)+2, &data_float, sizeof(data_float));
            else
                correctLen = false;
            break;
    }
    //шаг третий проверяем подходит ли длинна, если да то отправляем
    if (correctLen){
        Radio->stopListening();
        Radio->openWritingPipe(RF24_pipe);
        Radio->write(&data, 32);
        Radio->openReadingPipe(1, RF24_pipe);
        Radio->startListening();
        return true;
    }
    return false;
}

bool RF24Senosr::iteration(){
    bool sendRes = false;
    if(Radio->isChipConnected()){
        if(Radio->available()){
            #ifdef WriteLog_Serial
                Serial.print("Receved: ");
            #endif
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
            //отпарсиваем тип переданных данных
            char type = (char)data[topicLn+1];

            #ifdef WriteLog_Serial
                Serial.print(topicLn);
                Serial.print(' ');
                Serial.print(type);
                Serial.print(' ');
                Serial.print(topicName);
                Serial.print(' ');
            #endif
            
            int64_t value_int;
            char* value_char = new char [30 - topicLn];
            float value_float;
            //в зависимости от типа данных обрабатываем
            switch (type)
            {
            case 'i':   //передали интовое число
                memcpy(&value_int, data +topicLn + 2, sizeof(int));
                sendRes = Inter->send(topicName, const_cast<char*>((std::to_string(value_int)).c_str()));
                #ifdef WriteLog_Serial
                    Serial.print(value_int);
                    Serial.print(" Send to server: ");
                    Serial.println(sendRes);
                #endif
                break;
            case 's':   //передали строку
                memcpy(value_char, data + topicLn + 2, 30 - topicLn);
                sendRes = Inter->send(topicName, value_char);
                #ifdef WriteLog_Serial
                    Serial.println(value_char);
                    Serial.print(" Send to server: ");
                    Serial.println(sendRes);
                #endif
                break;
            case 'f':   //передали float
                
                memcpy(&value_float, data +topicLn + 2, sizeof(value_float));
                sendRes = Inter->send(topicName, const_cast<char*>((std::to_string(value_float)).c_str()));
                #ifdef WriteLog_Serial
                    Serial.print(value_float);
                    Serial.print(" Send to server: ");
                    Serial.println(sendRes);
                #endif
                break;
            case 'b':    //передали команду подписаться на топик
                sendRes = Inter->subscribe(topicName);
                break;
            }
        }
    }
    return sendRes;
}