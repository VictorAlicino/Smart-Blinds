#include <Arduino.h>
#include <Preferences.h>
#include <WiFi.h>
#include <Hardware.h>
#include <Connections.h>
#include <UserConfig.h>

//Global Variables
PubSubClient mqttClient(*(new WiFiClient()));
Preferences flash;
String device_name;
String ssid = WIFI_SSID;
String pass = WIFI_PASSWORD;
String mqtt_server_ip = MQTT_SERVER;
int mqtt_server_port = MQTT_SERVER_PORT;
String mqtt_user = MQTT_USER;
String mqtt_password = MQTT_PASSWORD;
static const char* TAG = "Main";
//end of Global Variables

//Global FLAGS
int WIFI_CONNECTION_STATUS;
int MQTT_CONNECTION_STATUS;
//end of Global FLAGS

void setup(){
    Serial.begin(115200); Serial.println();

    //Loading configs
    flash.begin("config");

    //Setting up name
    device_name = flash.getString("device_name", get_device_name());
    String name = "Persiana Inteligente ";
    name = name + "(" + device_name + ")";
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(name.c_str());
    ESP_LOGD(TAG, "Device Name: %s", device_name);
    //end of Setting up name

    flash.end();

    //Pins wake up
    activate_hardware();

    //Connecting to Wi-Fi
    while(WIFI_CONNECTION_STATUS != CONNECTED) {
        try {
            wifi_connect();
        } catch (...) {
            ESP_LOGD("WiFi Connection Error");
        }
    }

    //Connecting to MQTT Server
    while(MQTT_CONNECTION_STATUS != CONNECTED) {
        try {
            mqtt_connect();
        } catch (...) {
            ESP_LOGD("MQTT Connection Error");
        }
    }

}

void loop(){
    mqttClient.loop();
}