#include <Sensor_serva.h>

Sensor_serva::Sensor_serva(){}

Sensor_serva::Sensor_serva(Servo* sens){
    serva = sens;
    this->time = millis();
    this->angle_position = serva->read();
}

Sensor_serva::Sensor_serva(Interface* interf, Servo* sens){
    this->inte = interf;
    // Serial.begin(9600);
    // инициализируем датчика
    // DHT_Unified dht(DHTPIN, DHTTYPE);
    serva = sens;
    this->time = millis();
    this->angle_position = serva->read();
}

void Sensor_serva::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_serva::callback (char* topic, byte* message, unsigned int length){
    int64_t angle;
    memcpy(&angle, message, sizeof(int64_t));
    if (angle > 180){
        angle = 180;
    }
    if (angle < 0){
        angle = 0;
    }
    if ( abs(angle_position - angle) >= 1 ){
        serva->write(angle);
        angle_position = angle;
    }
    return true;
}

bool Sensor_serva::iteration(){
    if ( inte->loop() ){
        if (millis() - time > 5){
            uint8_t angle = serva->read();
            #ifdef WriteLog_SerialRF24
                Serial.print("angle: ");
                Serial.print(angle);
                Serial.println("grad");
            #endif
        }
    }
    return true;
}