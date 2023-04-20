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
}

void Sensor_oled::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled::callback (char* topic, byte* message, unsigned int length){
    int64_t angle;
    memcpy(&angle, message, sizeof(int64_t));
    return true;
}

bool Sensor_oled::iteration(){
    return inte->loop();
}