#ifndef _SENSORS_INTERFACE_
#define _SENSORS_INTERFACE_

#include "MQTT_interface.h"

class Sensor{
public:
    Sensor(const char* Name, bool (*func)(char* topic, byte* message, unsigned int length));    //инициализация сенсора, его название и ссылка на функцию-callback
    virtual bool iteration();   //опрос датчика, функция будет крутиться в main, переодически вызываясь
private:
    MQTTInterface mqtt;
    const char* name;
};

#endif