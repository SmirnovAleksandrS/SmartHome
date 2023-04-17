#include "Sensor_LED.h"

Sensor_LED::Sensor_LED(Interface* inter ,uint8_t pin){
    PIN = pin;
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, 1);
    delay(100);
    digitalWrite(PIN, 0);
    inte = inter;
}

bool Sensor_LED::iteration(){
    return true;
}

bool Sensor_LED::LED_Callback(char* topic, byte* message, unsigned int length){
    if (message[0] == '0'){
        digitalWrite(PIN, 0);
    } else {
        digitalWrite(PIN, 1);
    }
    return true;
}