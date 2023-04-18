#ifndef _DHT11_
#define _DHT11_

#include <Sensors_interface.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <RF24_settings.h>

class Sensor_DHT11 : public Sensor{
public:
    Sensor_DHT11();
    Sensor_DHT11(DHT_Unified* sens);
    Sensor_DHT11(Interface* interf, DHT_Unified* sens);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
protected:
    DHT_Unified* dht;
};

#endif