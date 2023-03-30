#ifndef _MQTT_INTERFACE_
#define _MQTT_INTERFACE_

#include <PubSubClient.h>
#include <MQTT_settings.h>
#include <WiFi.h>
#include <forward_list>

// class Sensor{
//   public:
//     //virtual void acceptChanges(const char* topic) = 0;  //topic - это топик, на который подписан датчик и в котором произошли изменения
// };

class Interface{
  public:
    virtual bool send(const char* topic, const char* data) = 0;
    virtual bool subscribe(const char* topic) = 0;
    virtual bool ifChanges() = 0;
    virtual bool loop() = 0;

  protected:
    bool hasChange;
    const char* name;     //название датчика
};

class MQTTInterface : public Interface{
  public:
    MQTTInterface(const char* Name);
    MQTTInterface(const char* Name, bool (*func)(char* topic, byte* message, unsigned int length));

    bool send(const char* topic, const char* data);  //отправка сообщений
    bool subscribe(const char* topic);
    bool ifChanges();
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

#endif