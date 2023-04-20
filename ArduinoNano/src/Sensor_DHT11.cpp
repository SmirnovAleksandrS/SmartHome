#include <Sensor_DHT11.h>

Sensor_DHT11::Sensor_DHT11(){}

Sensor_DHT11::Sensor_DHT11(Interface* interf, DHT_Unified* sens, const char* temp_top, const char* humid_top){
    this->inte = interf;

    dht = sens;
    dht->begin();
    this->humid_top = new char[strlen(humid_top) + 1];
    this->temp_top = new char[strlen(temp_top) + 1];
    for (unsigned int i=0; i < strlen(temp_top); i++){
        this->temp_top[i] = temp_top[i];
    }
    for (unsigned int i=0; i < strlen(humid_top); i++){
        this->humid_top[i] = humid_top[i];
    }
}

Sensor_DHT11::Sensor_DHT11(DHT_Unified* sens, const char* temp_top, const char* humid_top){
    dht = sens;
    dht->begin();
    this->humid_top = new char[strlen(humid_top) + 1];
    this->temp_top = new char[strlen(temp_top) + 1];
    for (unsigned int i=0; i < strlen(temp_top); i++){
        this->temp_top[i] = temp_top[i];
    }
    for (unsigned int i=0; i < strlen(humid_top); i++){
        this->humid_top[i] = humid_top[i];
    }
}

void Sensor_DHT11::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_DHT11::callback (char* topic, byte* message, unsigned int length){return true;}

bool Sensor_DHT11::iteration(){
if (inte->loop()){
        bool flag = true;
        if (millis() - time > 5000){
            sensors_event_t event;
            // получаем значение температуры
            dht->temperature().getEvent(&event);
            if (isnan(event.temperature)) {
                // в случае проблем с датчиком температуры выводим следующий текст
                #ifdef WriteLog_SerialRF24
                    Serial.println("Error reading temperature!");
                #endif
                flag = false;
            }
            else {
                // вывод в COM порт текста Temperature: xxx°C
                #ifdef WriteLog_SerialRF24
                    Serial.print("Temperature: ");
                    Serial.print(event.temperature);
                    Serial.println("C");
                #endif
                if (flag){
                flag = inte->send(temp_top, event.temperature);
                }
            }
            if (flag){
                // получаем значение влажности
                dht->humidity().getEvent(&event);
                if (isnan(event.relative_humidity)) {
                    // в случае проблем с датчиком влажности выводим следующий текст
                    #ifdef WriteLog_SerialRF24
                        Serial.println("Error reading humidity!");
                    #endif 
                    flag = false;       
                }
                else {
                    // вывод в COM порт текста Humidity: xxx%
                    #ifdef WriteLog_SerialRF24
                        Serial.print("Humidity: ");
                        Serial.print(event.relative_humidity);
                        Serial.println("%");
                    #endif
                    if (flag){
                        flag = inte->send(humid_top, event.relative_humidity);
                    }
                }
            }
            time = millis();
            return flag;
        }
    }
    return false;
}