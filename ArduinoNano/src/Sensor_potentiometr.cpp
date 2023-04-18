#include <Sensor_potentiometr.h>


Sensor_potentiometr::Sensor_potentiometr(Interface* interf, unsigned int port){
    this->inte = interf;
    // Serial.begin(9600);
    // инициализируем датчика
    // DHT_Unified dht(DHTPIN, DHTTYPE);
    this->time = millis();
    this->port = port;
    this->voltage = 0;
}

bool Sensor_potentiometr::potentiometr_Callback (char* topic, byte* message, unsigned int length){return true;}

bool Sensor_potentiometr::iteration(){
    if ( inte->loop() ){
        if (millis() - time > 5){
            bool flag = true;
            int16_t volt = analogRead(port);
            #ifdef WriteLog_SerialRF24
                Serial.print("Voltage: ");
                Serial.print(volt);
                Serial.println("parrot");
            #endif
            if ( abs(voltage - volt) >= 5 ){
                flag = inte->send("potent", (int64_t)volt);
            }
            voltage = volt;
            time = millis();
            return flag;
        }
    }
    return false;
}