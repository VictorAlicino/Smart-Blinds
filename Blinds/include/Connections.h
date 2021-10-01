//
// Created by victo on 01/10/2021.
//

#ifndef SMART_BLINDS_CONNECTIONS_H
#define SMART_BLINDS_CONNECTIONS_H


#include <Arduino.h>
#include <WiFi.h>

struct network_connection_error: public std::exception
{
    const char * what () const throw ()
    {
        return "Network Connection Error";
    }
};

struct mqtt_connection_error: public std::exception
{
    const char * what () const throw ()
    {
        return "MQTT Connection Error";
    }
};

void wifi_connect();

bool mqtt_connect();

IPAddress activate_internal_wifi();

void mqtt_callback(char* topic, byte* message, unsigned int length);

String get_mac_address();


#endif //SMART_BLINDS_CONNECTIONS_H
