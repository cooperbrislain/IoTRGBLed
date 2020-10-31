#ifndef IOTRGBLED_H
#define IOTRGBLED_H

#include <Arduino.h>
#include <string>
#include <iostream>
#include <map>

#include <SPI.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <StreamPrint.h>

#include "src/Light/Light.h"

#include "config.h"

struct Config {
    int    speed;
    int    fade;
    int    brightness;
    int    num_leds;
    int    num_lights;
    int    num_controls;
    int    num_params;
    int    bump_led;
    String name;
    String wifi_ssid;
    String wifi_pass;
};

void mqtt_callback(char* topic, byte* message, unsigned int length);
void reconnect();

Light::State* stateFromJson(JsonObject jsonState);

#endif // IOTRGBLED