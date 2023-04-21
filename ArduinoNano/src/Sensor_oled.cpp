#include <Sensor_oled.h>


Sensor_oled::Sensor_oled(){}

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oledd, const char* humid_top, const char* temp_top, const char* poten_top){
    // Serial.begin(9600);
    this->oled = oledd;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    // Serial.print(1);
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
    // Serial.print('k');

    // Serial.print('h');
    // oled->clear();
    // Serial.print(3);
    // oled->setScale(1);
    // Serial.print(4);
    // oled->setCursorXY(0, 5);
    // Serial.print(5);
    // oled->print("Humudity: ");
    // Serial.print(6);
    // oled->setCursorXY(0, 26);
    // oled->print("Tempature: ");
    // oled->setCursorXY(0, 47);
    // oled->print("Voltage: ");
    // oled->update();
    // Serial.print(4);
}

bool Sensor_oled::init(){

    Serial.print('h');
    oled->clear();
    Serial.print(3);
    oled->setScale(1);
    Serial.print(4);
    oled->setCursorXY(0, 5);
    Serial.print(5);
    oled->print("Humudity: ");
    Serial.print(6);
    oled->setCursorXY(0, 26);
    oled->print("Tempature: ");
    oled->setCursorXY(0, 47);
    oled->print("Voltahuige: ");
    oled->update();
    Serial.print(4);
}


void Sensor_oled::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled::callback (char* topic, byte* message, unsigned int length){
    int64_t temp;
    memcpy(&temp, message, sizeof(int64_t));
    char bufer[32];
    sprintf(bufer, "%i", temp);
    if (strcmp(topic, humid_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 5);
        oled->println(bufer);
        oled->update();
    }
    if (strcmp(topic, temp_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(95, 26);
        oled->println(bufer);
        oled->update();
    }
    if (strcmp(topic, poten_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 47);
        oled->println(bufer);
        oled->update();
    }

    return true;
}

bool Sensor_oled::iteration(){
    return inte->loop();
}