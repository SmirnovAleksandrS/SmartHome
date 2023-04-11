#ifndef _RF24_CONNECT_
#define _RF24_CONNECT_

#include <SPI.h>
#include <RF24.h>
#include <forward_list>
#include <Interface.h>
#include "Sensors_interface.h"
#include "RF24_settings.h"

bool startRf24(RF24* radio);
bool RF24_callback(char* topic, byte* message, unsigned int length);

class RF24Interface : public Interface{
public:
    RF24Interface();
    // RF24Interface();
    bool send(const char* topic, const char* data);
    bool subscribe(const char* topic);
    bool loop();
protected:
    bool (*callback) (char* topic, byte* message, unsigned int length);
    static std::forward_list<std::string> subscribedTopics; 
    static std::forward_list<std::forward_list<bool(*)(char* topic, byte* message, unsigned int length)>> subscribs;
};

class RF24Senosr : public Sensor{
public:
    RF24Senosr(Interface* inter, RF24* radio);

    bool iteration();
private:
    Interface* Inter;
    RF24* Radio;
};

#endif