#ifndef HARDWARE_H
#define HARDWARE_H

#include <Arduino.h>
#include <RotaryEncoder.h>


//Configurações
#define NUMBER_OF_BLINDS_SUPPORTED  1   /** Change in order to modify the number of Blinds supported by the device */
#define ENCODER_0_PIN_A             32  /** Encoder 0 First Pin */
#define ENCODER_0_PIN_B             33  /** Encoder 0 Second Pin */
#define MOTOR_0_PIN_A               18  /** Motor 0 First Pin */
#define MOTOR_0_PIN_B               19  /** Motor 0 Second Pin */
#define REED_SWITCH_0               4   /** Reed switch 0 Pin */


#if NUMBER_OF_BLINDS_SUPPORTED < 1
    #error At least 1 blind is required
#endif
#if NUMBER_OF_BLINDS_SUPPORTED > 4
    #error Blinds exceeds the limit of 4
#endif
#if NUMBER_OF_BLINDS_SUPPORTED >= 2
    #define ENCODER_1_PIN_A         (void *) 0  /** Encoder 1 First Pin */
    #define ENCODER_1_PIN_B         (void *) 0  /** Encoder 1 Second Pin */
    #define MOTOR_1_PIN_A           (void *) 0  /** Motor 1 First Pin */
    #define MOTOR_1_PIN_B           (void *) 0  /** Motor 1 Second Pin */
    #define REED_SWITCH_1           (void *) 0  /** Reedswitch 1 Pin */
#endif
#if NUMBER_OF_BLINDS_SUPPORTED >= 3
    #define ENCODER_2_PIN_A         (void *) 0  /** Encoder 2 First Pin */
    #define ENCODER_2_PIN_B         (void *) 0  /** Encoder 2 Second Pin */
    #define MOTOR_2_PIN_A           (void *) 0  /** Motor 2 First Pin */
    #define MOTOR_2_PIN_B           (void *) 0  /** Motor 2 Second Pin */
    #define REED_SWITCH_2           (void *) 0  /** Reedswitch 2 Pin */
#endif
#if NUMBER_OF_BLINDS_SUPPORTED == 4
    #define ENCODER_3_PIN_A         (void *) 0  /** Encoder 3 First Pin */
    #define ENCODER_3_PIN_B         (void *) 0  /** Encoder 3 Second Pin */
    #define MOTOR_3_PIN_A           (void *) 0  /** Motor 3 First Pin */
    #define MOTOR_3_PIN_B           (void *) 0  /** Motor 3 Second Pin */
    #define REED_SWITCH_3           (void *) 0  /** Reedswitch 3 Pin */
#endif

#define ACTIVATED HIGH 
#define DEACTIVATED LOW
 //Fim das configurações

enum CONNECTION_STATUS{
    NOT_READY,
    READY_TO_CONNECT,
    CONNECTED
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

/**
 * @brief Data type representation of a Blind and its components
 * 
 */
typedef struct BLINDS_DATA{
    RotaryEncoder *encoder;
    uint8_t motor_A;
    uint8_t motor_B;
    uint8_t reed_switch;
}Blind;

/**
 * @brief Get the device name
 * 
 * @return String The first two and the last two characters of the MAC Address
 */
String get_device_name();

/**
 * @brief Checks if the actual position matches the requested position. If they differ, the function calls the Up or Down functions
 * to adjust the blind to the desired position.
 * 
 */
void blind_check_position();

/**
 * @brief Moves the Blinds Down
 * 
 * @param blind_id ID of the desired blind in the device
 */
void blinds_down(uint8_t blind_id);

/**
 * @brief Moves the Blinds Up
 * 
 * @param blind_id ID of the desired blind in the device
 */
void blinds_up(uint8_t blind_id);

/**
 * @brief Stop the Blinds from moving
 * 
 * @param blind_id ID of the desired blind in the device
 */
void blinds_stop(uint8_t blind_id);

/**
 * @brief Set all the hardware connected for use
 * @details All the devices attached to pins in the device will be somehow prepared for use and the Blind will reset its
 * own position in order to guarantee a precise control
 * 
 */
void activate_hardware();

#endif