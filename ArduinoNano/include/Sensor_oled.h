#ifndef _OLED_
#define _OLED_

#include <Sensors_interface.h>
#include <RF24_settings.h>
#include <GyverOLED.h>
#include <math.h>
// GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;         -> write to main

class Sensor_oled : public Sensor{
public:
    Sensor_oled();
    Sensor_oled();
    Sensor_oled(Interface* interf);
    bool callback (char* topic, byte* message, unsigned int length);
    bool iteration();
    void setInterface(Interface* interf);
protected:
    uint8_t 
};


#endif