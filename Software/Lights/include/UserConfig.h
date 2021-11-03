//
// Created by victo on 28/10/2021.
//

#ifndef LIGHTS_USERCONFIG_H
#define LIGHTS_USERCONFIG_H

// ------------------ Wi-Fi Configurations  ----------------- //
/**
 * Change the SELF_WIFI Macro to "true" if you want the user to input the Wi-Fi Credentials via Webserver
 * or change to false in order to set the Wi-Fi Credentials in compilation time, be advised that error caused by
 * connection errors will not be treated in the SELF_WIFI false Mode. Be careful.
 */
#define SELF_WIFI           true
#define WIFI_SSID           "LabIoT"
#define WIFI_PASSWORD       "labiot2020."

/**
 * The WIFI_ATTEMPTS Macro will define how many times the device should try to connect to Wi-Fi before communicate
 * a failure.
 * This Macro is an Integer. Example: WIFI_ATTEMPTS 5
 */
#define WIFI_ATTEMPTS       5
// -------------- end of WiFi Configurations  -------------- //


// ------------------ MQTT Configurations  ----------------- //
/**
 * Change the SELF_MQTT Macro to "true" if you want the user to input the MQTT Credentials via Webserver
 * or change to false in order to set the MQTT Credentials in compilation time, be advised that error caused
 * by connection errors will not be treated in the SELF_MQTT false Mode. Be careful.
 */
#define SELF_MQTT               true

//If the MQTT Network requires Log-in via User and Password, set this variable to "true"
#define IS_MQTT_LOGIN_REQUIRED  false;

#define MQTT_USER               ""
#define MQTT_PASSWORD           ""
#define MQTT_SERVER             "192.168.1.103"
#define MQTT_SERVER_PORT        1883

#define MQTT_TOPIC_to_SUB       "0001"
#define MQTT_TOPIC_to_PUB       "qualquercoisa"

/**
 * The MQTT_ATTEMPTS Macro will define how many times the device should try to connect to the broker before communicate
 * a failure.
 * This Macro is an Integer. Example: MQTT_ATTEMPTS 5
 */
#define MQTT_ATTEMPTS       5
// -------------- end of MQTT Configurations  -------------- //

#endif //LIGHTS_USERCONFIG_H
