//
// Created by victo on 01/10/2021.
//

#ifndef SMART_BLINDS_USERCONFIG_H
#define SMART_BLINDS_USERCONFIG_H

// ------------------ WiFi Configurations  ----------------- //
#define WIFI_SSID           "LabIoT"
#define WIFI_PASSWORD       "labiot2020."
// -------------- end of WiFi Configurations  -------------- //

// ------------------ MQTT Configurations  ----------------- //
#define MQTT_USER           ""
#define MQTT_PASSWORD       ""
#define MQTT_SERVER         "192.168.1.103"
#define MQTT_SERVER_PORT    1883

#define MQTT_TOPIC_to_SUB   "0001"
#define MQTT_TOPIC_to_PUB   "qualquercoisa"
// -------------- end of MQTT Configurations  -------------- //


// ------------------ Blinds Configurations  ----------------- //
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
// -------------- end of Blinds Configurations  -------------- //

#endif //SMART_BLINDS_USERCONFIG_H
