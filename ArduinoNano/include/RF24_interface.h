#ifndef _RF24_CONNECT_
#define _RF24_CONNECT_

#include <SPI.h>
#include <RF24.h>
#include <Interface.h>
#include "RF24_settings.h"

bool startRf24(RF24* radio);

class RF24Interface : public Interface{
public:
    RF24Interface();
    bool send(const char* topic, const char* data);
    bool subscribe(const char* topic);
    bool loop();
protected:
    static RF24* Radio;
    bool (*callback) (char* topic, byte* message, unsigned int length);
    // static list<string> subscribedTopics; 
    // static list<std::list<bool(*)(char* topic, byte* message, unsigned int length)>> subscribs;
};

#endif