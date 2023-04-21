#include <Sensor_oled_two.h>


Sensor_oled_two::Sensor_oled_two(){}

Sensor_oled_two::Sensor_oled_two(OLED* oledd, const char* humid_top, const char* temp_top, const char* poten_top){
    extern uint8_t TinyFont[];
    extern uint8_t SmallFont[];
    extern uint8_t MediumNumbers[];
    extern uint8_t BigNumbers[];
    this->oled = oledd;
    this->temp = 0;
    this->humid = 0;
    this->poten = 0;
    Serial.print(1);
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
    
    this->oled = oledd;
    oled->begin();
    oled->setFont(TinyFont);
    oled->print("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LEFT, 10);
    oled->update();
    delay(1000);
}

Sensor_oled_two::Sensor_oled_two(OLED* oledd, Interface* interf, const char* humid_top, const char* temp_top, const char* poten_top){
    this->inte = interf;

    extern uint8_t TinyFont[];
    extern uint8_t SmallFont[];
    extern uint8_t MediumNumbers[];
    extern uint8_t BigNumbers[];
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

    this->oled = oledd;
    oled->begin();
    oled->setFont(TinyFont);
    oled->print("ABCDEFGHIJKLMNOPQRSTUVWXYZ", LEFT, 10);
    oled->update();
    delay(1000);
}

void Sensor_oled_two::setInterface(Interface* interf){
    inte = interf;
}

bool Sensor_oled_two::callback (char* topic, byte* message, unsigned int length){
    int64_t temp;
    memcpy(&temp, message, sizeof(int64_t));
    char bufer[32];
    sprintf(bufer, "%i", temp);
    if (strcmp(topic, humid_top) == 0){
        
    }
    if (strcmp(topic, temp_top) == 0){
        
    }
    if (strcmp(topic, poten_top) == 0){
        
    }

    return true;
}

bool Sensor_oled_two::iteration(){
    return inte->loop();
}