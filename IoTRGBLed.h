#ifndef IOTRGBLED_H
#define IOTRGBLED_H

#include <Arduino.h>
#include <string>
#include <iostream>

#include <SPIFFS.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <StreamPrint.h>

#include <Action.h>
#include <Light.h>

#include "config.h"

struct Config {
    String name;
    String wifi_ssid;
    String wifi_pass;
};

void mqtt_callback(char* topic, byte* message, unsigned int length);
void reconnect();

#endif // IOTRGBLED