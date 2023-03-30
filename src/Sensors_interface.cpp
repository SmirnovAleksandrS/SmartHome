#include "Sensors_interface.h"

Sensor::Sensor(const char* Name, bool (*func)(char* topic, byte* message, unsigned int length) ) {
    name = Name;
    mqtt = MQTTInterface(name, func);
}