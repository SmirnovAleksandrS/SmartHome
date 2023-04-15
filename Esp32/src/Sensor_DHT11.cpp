#include <Sensor_DHT11.h>
#include <MQTT_interface.h>

Sensor_DHT11::Sensor_DHT11(Interface* interf){
    this->inte = interf;
}

bool Sensor_DHT11::iteration(){
    return true;
}