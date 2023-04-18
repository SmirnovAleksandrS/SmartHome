#ifndef _SERVA_
#define _SERVA_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <Servo.h>
#include <math.h>

class Sensor_serva : public Sensor{
public:
    Sensor_serva();
    Sensor_serva(Interface* interf, Servo* sens);
    bool potentiometr_Callback (char* topic, byte* message, unsigned int length);
    // Sensor_DHT11(Interface* interf, uint8_t port);

    // void stPort(port);
    // begin()

    bool iteration();
protected:
    Servo* serva;
    uint64_t time;
    uint8_t angle_position;
};


#endif