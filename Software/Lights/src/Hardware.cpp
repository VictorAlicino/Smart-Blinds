#include <Arduino.h>
#include <PubSubClient.h>
#include <Preferences.h>

#include <utility>
#include "Hardware.h"
#include "esp_system.h"

extern PubSubClient mqttClient;
extern String device_name;
extern Preferences flash;

struct dimmer_error: public std::exception
{
    const char * what () const throw ()
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

void activate_hardware(){
	ESP_LOGD("Hardware", "Initializing the Hardware");

}

Light::Light(int GP_IO, String name, bool is_dimmable){
	digitalWrite(GP_IO, DEACTIVATED);
	this->power_state = DEACTIVATED;
	this->dimmable = is_dimmable;
	this->dimmer_value = 0x00;
	this->name = std::move(name);
}

bool Light::is_dimmable() const{
	return dimmable;
}

bool Light::get_power_state() const{
	return power_state;
}

unsigned int Light::get_dimmer_value() const{
	return this->dimmer_value;
}

void Light::set_dimm_value_to(unsigned int value){
    if(!(value >0 && value < 255)){
        throw dimmer_error();
    }
    this->dimmer_value = value;
}

String Light::get_name(){
	return this->name;
}