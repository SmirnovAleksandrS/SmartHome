#include <Sensor_oled.h>


Sensor_oled::Sensor_oled(){}

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled, const char* humid_top, const char* temp_top, const char* poten_top){
    this->oled = oled;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    this->humid_top = new char[strlen(humid_top) + 1];
    for (unsigned int  i=0; i < strlen(humid_top); i++){
        this->humid_top[i] = humid_top[i];
    }
    this->temp_top = new char[strlen(temp_top) + 1];
    for (unsigned int  i=0; i < strlen(temp_top); i++){
        this->temp_top[i] = temp_top[i];
    }
    this->poten_top = new char[strlen(poten_top) + 1];
    for (unsigned int  i=0; i < strlen(poten_top); i++){
        this->poten_top[i] = poten_top[i];
    }
    oled->init();        // инициализация
    oled->clear();       // очистка
    oled->setScale(3);   // масштаб текста (1..4)
    oled->home();        // курсор в 0,0
    oled->print("Привет!");
    delay(1000);
    oled->setScale(1);
    // курсор на начало 3 строки
    oled->setCursor(0, 3);
    oled->print("GyverOLED v1.3.2");
    // курсор на (20, 50)
    oled->setCursorXY(20, 50);
    float pi = 3.14;
    oled->print("PI = ");
    oled->print(pi);
    delay(1000);
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

Sensor_oled::Sensor_oled(GyverOLED<SSD1306_128x64, OLED_NO_BUFFER>* oled, Interface* interf, const char* humid_top, const char* temp_top, const char* poten_top){
    this->inte = interf;

    this->oled = oled;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    this->humid_top = new char[strlen(humid_top) + 1];
    for (unsigned int  i=0; i < strlen(humid_top); i++){
        this->humid_top[i] = humid_top[i];
    }
    this->temp_top = new char[strlen(temp_top) + 1];
    for (unsigned int  i=0; i < strlen(temp_top); i++){
        this->temp_top[i] = temp_top[i];
    }
    this->poten_top = new char[strlen(poten_top) + 1];
    for (unsigned int  i=0; i < strlen(poten_top); i++){
        this->poten_top[i] = poten_top[i];
    }
    oled->init();        // инициализация
    oled->clear();       // очистка
    oled->setScale(3);   // масштаб текста (1..4)
    oled->home();        // курсор в 0,0
    oled->print("Привет!");
    delay(1000);
    oled->setScale(1);
    // курсор на начало 3 строки
    oled->setCursor(0, 3);
    oled->print("GyverOLED v1.3.2");
    // курсор на (20, 50)
    oled->setCursorXY(20, 50);
    float pi = 3.14;
    oled->print("PI = ");
    oled->print(pi);
    delay(1000);
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
    int64_t temp;
    memcpy(&temp, message, sizeof(int64_t));
    if (strcmp(topic, humid_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 5);
        oled->println(temp);
        oled->update();
    }
    if (strcmp(topic, temp_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(95, 26);
        oled->println(temp);
        oled->update();
    }
    if (strcmp(topic, poten_top) == 0){
        oled->setScale(2);
        oled->setCursorXY(70, 47);
        oled->println(temp);
        oled->update();
    }

    return true;
}

bool Sensor_oled::iteration(){
    return inte->loop();
}