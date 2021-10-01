//
// Created by victo on 01/10/2021.
//
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <DNSServer.h>
#include "Connections.h"
#include "WebServers.h"
#include "Hardware.h"

extern String device_name;
extern Preferences flash;
extern PubSubClient mqttClient;
extern DNSServer dnsServer;
extern String ssid;
extern String pass;
extern String mqtt_server_ip;
extern int mqtt_server_port;
extern int WIFI_CONNECTION_STATUS;
extern int MQTT_CONNECTION_STATUS;
__attribute__((unused)) extern String mqtt_user;
__attribute__((unused)) extern String mqtt_password;
static const char* TAG = "Connections";

void wifi_connect(){
    try{
        flash.begin("config");
        WiFi.begin(ssid.c_str(), pass.c_str());
        ESP_LOGD(TAG, "Connecting to WiFi");
        const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

        //Aguardando a primeira tentativa de conexão
        vTaskDelay(xDelay*5);

        //Realizando mais tentativas
        int attemps = 5;
        for(int counter = 0; WiFi.status() != WL_CONNECTED && counter < attemps; counter++){
            vTaskDelay(xDelay*5);
            ESP_LOGE(TAG, "Connection Failed! %d Attemps remaining!", attemps - counter);
            ESP_LOGD(TAG, "Retrying...");
        }
        if(WiFi.status() != WL_CONNECTED){
            ESP_LOGE(TAG, "Connection failed after %d attemps.", attemps);
            flash.end();
            throw network_connection_error();
        }else{
            WIFI_CONNECTION_STATUS = CONNECTED;
            ESP_LOGD(TAG, "Connected");
            flash.putString("wifi_ssid", ssid);
            flash.putString("wifi_password", pass);
            ESP_LOGD(TAG, "WiFi Credentials has been written in memory");
            flash.end();
        }
    }catch(std::exception& e){
        WIFI_CONNECTION_STATUS = NOT_READY;
        ESP_LOGE(TAG, "Network Connection Error -> Throwing Exception.");
        throw e;
    }
}

IPAddress activate_internal_wifi(){
    ESP_LOGD(TAG, "Initializing Internal Wireless Netowrk");
    String name = "Persiana Inteligente ";
    name = name + "(" + device_name + ")";
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(name.c_str(), NULL);
    IPAddress IP = WiFi.softAPIP();
    dnsServer.start(53, "*", IP);
    ESP_LOGD(TAG, "Starting DNS Server");
    WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
    WiFi.setHostname(name.c_str());
    ESP_LOGI(TAG, "Configuration Access Point set on %s", IP.toString().c_str());
    return IP;
}

bool mqtt_connect(){
    try{
        flash.begin("config");
        if(WIFI_CONNECTION_STATUS == CONNECTED){
            mqttClient.setServer(mqtt_server_ip.c_str(), mqtt_server_port);
            String name = "Persiana " + device_name;
            mqttClient.connect(name.c_str());
            mqttClient.setCallback(mqtt_callback);
            if(mqttClient.connected() != true){
                throw mqtt_connection_error();
            }
            mqttClient.subscribe(MQTT_TOPIC_to_SUB);
            mqttClient.publish(MQTT_TOPIC_to_PUB,"hello world");
            MQTT_CONNECTION_STATUS = CONNECTED;
            ESP_LOGD(TAG, "MQTT Connected");
            flash.putString("mqtt_ip", mqtt_server_ip);
            flash.putInt("mqtt_port", mqtt_server_port);
            ESP_LOGD(TAG, "MQTT Credentials has been written in memory");
            flash.end();
        }else{
            MQTT_CONNECTION_STATUS = NOT_READY;
            flash.end();
            throw mqtt_connection_error();
        }
    }
    catch(std::exception& e){
        MQTT_CONNECTION_STATUS = NOT_READY;
        ESP_LOGE(TAG, "MQTT Connection Error -> Throwing Exception.");
        throw e;
    }
}

void mqtt_callback(char* topic, byte* message, unsigned int length){
    ESP_LOGD(TAG, "Data Received");

    if(!strcmp(topic, MQTT_TOPIC_to_SUB)){
        char buffer[length + 1];
        for(int i = 0; i < length; i++) {
            buffer[i] = message[i];
        }
        buffer[length] = '\0';

        if (strcmp(buffer, "0001") == 0) {
            blinds_down(0);
            ESP_LOGD(TAG, "Abrindo Persiana");
        }else if (strcmp(buffer, "0002") == 0) {
            blinds_up(0);
            ESP_LOGD(TAG, "Fechando Persiana");
        }else if (strcmp(buffer, "0003") == 0){
            blinds_stop(0);
            ESP_LOGD(TAG, "Parando Imediatamente");
        }else{
            ESP_LOGE(TAG, "Não foi possível processar a mensagem");
        }
    }
}

String get_mac_address(){
    uint8_t baseMac[6];
    // Get MAC address for WiFi station
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    char baseMacChr[18] = {0};
    sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
    return String(baseMacChr);
}
