#include <Arduino.h>
#include <RotaryEncoder.h>
#include <Preferences.h>
#include <PubSubClient.h>
#include <DNSServer.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>

#include "Hardware.h"

//Global Variables
PubSubClient mqttClient(*(new WiFiClient()));
Blind Blinds[NUMBER_OF_BLINDS_SUPPORTED];
Preferences flash;
String device_name;
DNSServer dnsServer;
AsyncWebServer server(80);
String ssid;
String pass;
String mqtt_server_ip;
int mqtt_server_port;
String mqtt_user;
String mqtt_password;
//End of Global Variables

//FLAGS
int WIFI_CONNECTION_STATUS;
int MQTT_CONNECTION_STATUS;
//Fim das FLAGS

/**
 * @brief
 *
 */
void setup(){
    // ----> BOOT <---- //
    //Initializing Serial Port
    Serial.begin(115200); Serial.println();
    //End of Initializing Serial Port

    //Load configurations
    flash.begin("config");

    //In case of first boot, the device will enter in Configuration Mode
    bool first_boot = flash.getBool("first_boot", true);
    // ----> END_BOOT <---- //

    if (!first_boot) {

    } else {
        // ----> ACTIVATE CONFIGURATION WEBSERVER <---- //
        ESP_LOGD("Main", "This device is not configured yet");
        WIFI_CONNECTION_STATUS = NOT_READY;

        //Definindo o nome
        device_name = get_device_name();
        ESP_LOGD("Main", "%s", device_name);
        flash.putString("device_name", device_name);
        ESP_LOGD("Main", "Device Name: %s", device_name);

        flash.end();
        //End of Load configurations

        //Ativando Web Server
        IPAddress IP = activate_internal_wifi();
        startup_server();

        // ----> END_ACTIVATE CONFIGURATION WEBSERVER <---- //
        //Ativando Bluetooth
        //TODO Bluetooth

        //Loop de Configuração
        while(true){
            if(WIFI_CONNECTION_STATUS == READY_TO_CONNECT){
                try{
                    wifi_connect();
                    flash.end();
                    server.end();
                }catch(...){
                    ESP_LOGD("WiFi Connection Error");
                }
            }
            if((WIFI_CONNECTION_STATUS == CONNECTED) && (MQTT_CONNECTION_STATUS == READY_TO_CONNECT)){
                try{
                    mqtt_connect();
                    flash.putBool("first_boot", false);
                    mqttClient.disconnect();
                    flash.end();
                    server.end();
                    ESP.restart();
                }catch(...){
                    ESP_LOGD("MQTT Connection Error");
                }
            }
            dnsServer.processNextRequest();
            //mqttClient.loop();
        }
    }
}

/**
 * @brief
 *
 */
void loop(){

}