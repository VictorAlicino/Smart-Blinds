#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <UserConfig.h>


//Configurações
#define ACTIVATED HIGH
#define DEACTIVATED LOW
//Fim das configurações


enum CONNECTION_STATUS{
    NOT_READY,
    READY_TO_CONNECT,
    CONNECTED
};

enum DEVICE_STATUS{
    IN_PROGRESS,
    READY,
    DONE,
    FAILURE,
    CRITICAL_FAILURE
};

enum MESSAGES_IDENTIFIERS{
    SERVER_RECEIVED         = 0x00,
    DEVICE_SEND             = 0X01,
    DEVICE_GENERIC_ERROR    = 0x02,
};

enum MODE{
    BLINDS_STOP         = 0X00,
    BLINDS_UP           = 0X01,
    BLINDS_DOWN         = 0X02,
    BLINDS_LINEAR_VALUE = 0x03,
};

class Light{
private:
    bool power_state;
    bool dimmable;
    float dimmer_value;
    String name;

public:
    Light(int GPIO, String name, bool is_dimmable);

    bool is_dimmable();

    bool get_power_state();

    int get_dimmer_value();

    unsigned int set_dimm_value_to(unsigned int value);

    String get_name();
};

/**
 * @brief Get the device name
 * 
 * @return String The first two and the last two characters of the MAC Address
 */
String get_device_name();

/**
 * @brief Set up all the hardware connected for use
 * @details
 * 
 */
void activate_hardware();

#endif