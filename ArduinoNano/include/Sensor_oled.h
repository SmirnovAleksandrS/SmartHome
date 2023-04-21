#ifndef _OLED_
#define _OLED_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <GyverOLED.h>
#include <math.h>
        //-> write to main

class Sensor_oled : public Sensor{
public:
    Sensor_oled();
    Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled, const char* humid_top, const char* temp_top, const char* poten_top);
    Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled, Interface* interf, const char* humid_top, const char* temp_top, const char* poten_top);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
    // int Order(int num);
    // bool ItoA(int num, char* buffer, size_t buffer_size);
protected:
    GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled; 
    char* humid_top;
    char* temp_top;
    char* poten_top;
    uint64_t humid;
    uint64_t temp;
    uint64_t poten;
};


#endif