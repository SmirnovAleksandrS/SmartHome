#ifndef _OLED_TWO_
#define _OLED_TWO_

#include <Sensors_interface.h>
#include "OLED_I2C.h" 
#include <RF24_settings.h>
        //-> write to main

class Sensor_oled_two : public Sensor{
public:
    Sensor_oled_two();
    Sensor_oled_two(OLED* oledd, const char* humid_top, const char* temp_top, const char* poten_top);
    Sensor_oled_two(OLED* oledd, Interface* interf, const char* humid_top, const char* temp_top, const char* poten_top);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
    // int Order(int num);
    // bool ItoA(int num, char* buffer, size_t buffer_size);
protected:
    OLED* oled; 
    char* humid_top;
    char* temp_top;
    char* poten_top;
    uint64_t humid;
    uint64_t temp;
    uint64_t poten;
};


#endif