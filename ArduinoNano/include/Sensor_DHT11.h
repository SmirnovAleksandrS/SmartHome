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
    Sensor_DHT11(Interface* interf, DHT_Unified* sens);
    bool DHT11_Callback (char* topic, byte* message, unsigned int length);
    // Sensor_DHT11(Interface* interf, uint8_t port);

    // void stPort(port);
    // begin()

    bool iteration();
protected:
    DHT_Unified* dht;
};

#endif