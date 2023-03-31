#ifndef _DHT11_
#define _DHT11_

#include <Sensors_interface.h>

class Sensor_DHT11 : public Sensor{
public:
    Sensor_DHT11();
    Sensor_DHT11(const char*, Interface* interf);

    bool iteration();
protected:

};

#endif