#include <Arduino.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <new>

#include <utility>
#include "Hardware.h"
#include "esp_system.h"

extern PubSubClient mqttClient;
extern String device_name;
extern Preferences flash;
static const char* TAG = "Hardware";
std::vector<Light> Lights;

struct dimmer_error: public std::exception
{
    const char * what () const noexcept override
    {
        return "Dimmer Value Error";
    }
};

String get_device_name(){
	uint8_t baseMac[6];
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	char baseMacChr[18] = {0};
	sprintf(baseMacChr, "%02X%02X", baseMac[0], baseMac[5]);
	return {baseMacChr};
}

void activate_hardware() {
    ESP_LOGD("Hardware", "Initializing the Hardware");

    Lights.reserve(8);

    Lights.emplace_back(GP_CONTROL_1, "Luz 1", false);
    Lights.emplace_back(GP_CONTROL_2, "Luz 2", false);
    Lights.emplace_back(GP_CONTROL_3, "Luz 3", false);
    Lights.emplace_back(GP_CONTROL_4, "Luz 4", false);
    Lights.emplace_back(GP_CONTROL_5, "Luz 5", false);
    Lights.emplace_back(GP_CONTROL_6, "Luz 6", false);
    Lights.emplace_back(GP_CONTROL_7, "Luz 7", false);
    Lights.emplace_back(GP_CONTROL_8, "Luz 8", false);

    for(auto& it:Lights){
        it.pulse(PULSE_MS);
        ESP_LOGD(TAG, "%s Pulse", it.getName().c_str());
    }
}

Light::Light(uint8_t GPIO, const char *name, bool is_dimmable) {
    this->pin = GPIO;
    pinMode(this->pin, OUTPUT);
    this->dimmable = is_dimmable;
    digitalWrite(this->pin, DEACTIVATED);
    this->name = String(name);
    this->dimmer_value = 0x00;
    this->power_state = DEACTIVATED;
    ESP_LOGD(TAG, "Light Object Created");
}

uint8_t Light::getPin() const {
    return pin;
}

void Light::setPin(uint8_t pin) {
    Light::pin = pin;
}

bool Light::isPowerState() const {
    return power_state;
}

void Light::setPowerState(bool powerState) {
    power_state = powerState;
}

bool Light::isDimmable() const {
    return dimmable;
}

void Light::setDimmable(bool dimmable) {
    Light::dimmable = dimmable;
}

uint8_t Light::getDimmerValue() const {
    return dimmer_value;
}

void Light::setDimmerValue(uint8_t dimmerValue) {
    dimmer_value = dimmerValue;
}

const String &Light::getName() const {
    return name;
}

void Light::setName(const String &name) {
    Light::name = name;
}

void Light::on(){
    if(this->dimmable){

    }else{
        digitalWrite(this->pin, ACTIVATED);
    }
    this->power_state = ACTIVATED;
    ESP_LOGD(TAG, "%s is now On", this->name.c_str());
}

void Light::off(){
    if(this->dimmable){

    }else{
        digitalWrite(this->pin, DEACTIVATED);
    }
    this->power_state = DEACTIVATED;
    ESP_LOGD(TAG, "%s is now Off", this->name.c_str());
}

void Light::pulse(uint8_t ms){
    digitalWrite(this->pin, (this->power_state == ACTIVATED ? DEACTIVATED : ACTIVATED));
    this->power_state = !(this->power_state);
    vTaskDelay(ms/portTICK_PERIOD_MS);
    digitalWrite(this->pin, !this->power_state);
    this->power_state = !(this->power_state);
}

