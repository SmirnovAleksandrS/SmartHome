#include <Sensor_DHT11.h>


Sensor_DHT11::Sensor_DHT11(Interface* interf, DHT_Unified* sens){
    this->inte = interf;
    // Serial.begin(9600);
    // инициализируем датчика
    // DHT_Unified dht(DHTPIN, DHTTYPE);
    dht = sens;
    dht->begin();
    
}

Sensor_DHT11::Sensor_DHT11(DHT_Unified* sens){
    dht = sens;
    dht->begin();
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
                }
            }
            if (flag){
                flag = inte->send("dht11_temp", event.temperature);
                if (flag){
                    flag = inte->send("dht11_humid", event.relative_humidity);
                }
            }
            time = millis();
            return flag;
        } else {
            return 1;
        }
    }
    return false;
}