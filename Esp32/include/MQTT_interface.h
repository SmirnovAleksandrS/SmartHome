#ifndef _MQTT_INTERFACE_
#define _MQTT_INTERFACE_

#include <Interface.h>
#include <forward_list>
#include <PubSubClient.h>
#include <WiFi.h>
#include <MQTT_settings.h>

class MQTTInterface : public Interface{
  public:
    MQTTInterface();
    MQTTInterface(const char* Name);
    MQTTInterface(const char* Name, bool (*func)(char* topic, byte* message, unsigned int length));

    bool send(const char* topic, const char* data);   //отправка сообщений
    // bool send(const char* topic, int32_t data); 
    bool subscribe(const char* topic);                //подписка на топик
    bool loop();
    bool isConnect();
    void setCallback(bool (*func)(char* topic, byte* message, unsigned int length));
    static void MQTTcallback(char* topic, byte* message, unsigned int length);

  protected:
    bool (*callback) (char* topic, byte* message, unsigned int length);
    static WiFiClient WFClient;
    static PubSubClient* PSClient;
    static std::forward_list<std::string> subscribedTopics; 
    static std::forward_list<std::forward_list<bool(*)(char* topic, byte* message, unsigned int length)>> subscribs;
};


bool startMQTT(PubSubClient* client);   // функция запуска всех интерфейсов, подключение к Wi-Fi и MQTT серверу

#endif