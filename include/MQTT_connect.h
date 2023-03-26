#ifndef _MQTT_CONNECT_
#define _MQTT_CONNECT_

#include <PubSubClient.h>
#include <WiFi.h>
#include <MQTT_settings.h>
#include <MQTT_interface.h>

bool start(PubSubClient* client);   // функция запуска всех интерфейсов, подключение к Wi-Fi и MQTT серверу

#endif