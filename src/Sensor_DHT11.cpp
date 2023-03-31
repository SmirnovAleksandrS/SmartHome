#include <Sensor_DHT11.h>
#include <MQTT_interface.h>

Sensor_DHT11::Sensor_DHT11(const char*, Interface* interf){

}

bool Sensor_DHT11::iteration(){
    return true;
}