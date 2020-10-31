#include "IoTRGBLed.h"

WiFiClient      espClient;
PubSubClient    client(espClient);

const char* wifi_ssid = WIFI_SSID;
const char* wifi_pass = WIFI_PASS;
const char* mqtt_host = MQTT_HOST;

Config      config;
CRGB*      leds;
Light**    lights;

std::map<String, Action*>       actions;
std::map<String, Light::State*> states;
std::map<String, Light*>        lightMap;

int count = 0;

void setup() {
    Serial.begin(115200);

    Serial.println("Starting up IoT RGB LED Strips");

    Serial << "Loading configuration...\n";
    SPIFFS.begin(true);
    StaticJsonDocument<4096> jsonDoc;
    File configFile = SPIFFS.open("/config.json", FILE_READ);
    deserializeJson(jsonDoc, configFile);
    configFile.close();

    JsonObject obj      = jsonDoc.as<JsonObject>();

    config.name         = jsonDoc["name"].as<String>() || "Unnamed Project";
    config.wifi_ssid    = jsonDoc["wifi_ssid"].as<String>();
    config.wifi_pass    = jsonDoc["wifi_pass"].as<String>();

    pinMode(LED_PIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);

    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_GPIO32_CHANNEL, ADC_ATTEN_DB_0);

    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);

    WiFi.begin(wifi_ssid, wifi_pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected with IP: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_host, 1883);
    client.setCallback(mqtt_callback);

    Serial.println("Starting Lights...");
}

void main() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    delay(5000);
}

void mqtt_callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "/esp32/read") {
        Serial.println("Reading... ");
        // do stuff;
    }
    if (String(topic) == "/esp32") {

    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("connected");
            client.subscribe("/esp32/read");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}