#include <Arduino.h>
#include <PubSubClient.h>
#include <Preferences.h>
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

Light::Light(int GPIO, String name, bool is_dimmable){
	digitalWrite(GPIO, DEACTIVATED);
	this->power_state = DEACTIVATED;
	this->dimmable = is_dimmable;
	this->dimmer_value = 0x00;
	this->name = name;
}

bool Light::is_dimmable(){
	return dimmable ? true : false;
}

bool Light::get_power_state(){
	return power_state ? true : false;
}

int Light::get_dimmer_value(){
	return this->dimmer_value;
}

unsigned int Light::set_dimm_value_to(unsigned int value){
	if value > 0 && value < 255 ? dimmer_value = value : throw dimmer_error;
}

String Light::get_name(){
	return this->name;
}