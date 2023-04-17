#ifndef _SENSOR_LED_
#define _SENSOR_LED_

#include "Sensors_interface.h"

class Sensor_LED : public Sensor{
public:
    Sensor_LED(Interface* inter ,uint8_t pin);
    bool iteration();
    static bool LED_Callback (char* topic, byte* message, unsigned int length);

    
protected:
    static uint8_t PIN;
    // Interface* Inter; прописан в родительском классе
};

#endif