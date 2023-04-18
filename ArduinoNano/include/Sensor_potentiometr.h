#ifndef _POTENTIOMETR_
#define _POTENTIOMETR_


#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <math.h>

class Sensor_potentiometr : public Sensor{
public:
    Sensor_potentiometr();
    Sensor_potentiometr(Interface* interf, unsigned int port);
    bool potentiometr_Callback (char* topic, byte* message, unsigned int length);
    // Sensor_DHT11(Interface* interf, uint8_t port);

    // void stPort(port);
    // begin()

    bool iteration();
protected:
    uint64_t time;
    int16_t voltage;
    unsigned int port;
};


#endif 