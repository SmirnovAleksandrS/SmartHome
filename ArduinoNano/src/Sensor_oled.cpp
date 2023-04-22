#include <Sensor_oled.h>


Sensor_oled::Sensor_oled(){}

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oledd, const char* humid_top, const char* temp_top, const char* poten_top){
    // Serial.begin(9600);
    this->oled = oledd;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    this->humid_top = new char[strlen(humid_top) + 1];
    for (unsigned int  i=0; i <= strlen(humid_top); i++){
        this->humid_top[i] = humid_top[i];
    }
    this->temp_top = new char[strlen(temp_top) + 1];
    for (unsigned int  i=0; i <= strlen(temp_top); i++){
        this->temp_top[i] = temp_top[i];
    }
    this->poten_top = new char[strlen(poten_top) + 1];
    for (unsigned int  i=0; i <= strlen(poten_top); i++){
        this->poten_top[i] = poten_top[i];
    }
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
    oled->setCursorXY(70, 47);
    oled->print("1453");
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