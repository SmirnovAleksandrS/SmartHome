#include <Sensor_oled.h>


Sensor_oled::Sensor_oled(){}

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oledd, const char* humid_topic, const char* temp_topic, const char* poten_topic){
    // Serial.begin(9600);
    this->oled = oledd;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    this->humid_top = new char[strlen(humid_top) + 1];
    memcpy(humid_top, humid_topic, strlen(humid_topic) + 1);
    this->temp_top = new char[strlen(temp_top) + 1];
    memcpy(temp_top, temp_topic, strlen(temp_topic) + 1);
    this->poten_top = new char[strlen(poten_top) + 1];
    memcpy(poten_top, poten_topic, strlen(poten_topic) + 1);
}

bool Sensor_oled::init(){

    oled->clear();
    oled->setScale(1);
    oled->setCursorXY(0, 5);
    oled->print("Humudity: ");
    oled->setCursorXY(0, 26);
    oled->print("Tempature: ");
    oled->setCursorXY(0, 47);
    oled->print("Voltage: ");
    oled->update();
}


void Sensor_oled::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled::callback (char* topic, byte* message, unsigned int length){
    // char temp;
    // memcpy(&temp, message, sizeof(int64_t));
    char* temp_str = reinterpret_cast<char*>(message);
    // char bufer[32];
    // sprintf(bufer, "%i", temp);
    if (strcmp(topic, humid_top) == 0){
        oled->setScale(1);
        oled->setCursorXY(70, 5);
        oled->println(temp_str);
        oled->update();
    }
    if (strcmp(topic, temp_top) == 0){
        oled->setScale(1);
        oled->setCursorXY(95, 26);
        oled->println(temp_str);
        oled->update();
    }
    if (strcmp(topic, poten_top) == 0){
        oled->setScale(1);
        oled->setCursorXY(70, 47);
        oled->println(temp_str);
        oled->update();
    }

    return true;
}

bool Sensor_oled::iteration(){
    return inte->loop();
}