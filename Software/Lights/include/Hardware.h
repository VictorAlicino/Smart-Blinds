#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <UserConfig.h>


//Configurações
#define ACTIVATED LOW
#define DEACTIVATED HIGH
//Fim das configurações


typedef unsigned int uint_8t;
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
    LIGHTS_ON           = 0X00,
    LIGHTS_OFF          = 0X01,
    LIGHTS_VALUE_CHANGE = 0X02,
};

/**
 * @brief Light controls Class
 */
class Light{
private:
    uint8_t pin;
    uint8_t switch_pin;
    bool power_state;
    bool dimmable;
    bool is_active;
    uint8_t dimmer_value;
    String name;

public:
    /**
     *
     * @param GPIO_Light
     * @param GPIO_Switch
     * @param name
     * @param is_dimmable
     */
    Light(uint8_t GPIO_Light, uint8_t GPIO_Switch, const char* name, bool is_dimmable);

    /**
     *
     */
    void on();

    /**
     *
     */
    void off();

    /**
     *
     * @param ms
     */
    void pulse(uint8_t ms);

    String getName();

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