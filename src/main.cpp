#include "settings.h"
#include <Arduino.h>
#include <LittleFS.h>
#include "MyOta.h"
#include "MyWifi.h"
#include "TallySystem.h"

char my_ota_password[] = OTA_PASS;
char my_esp_hostname[] = ESP_HOSTNAME;

TallySystem tallySystem(my_ota_password);
void setup() {
	Serial.begin(115200);
	delay(500);
	LittleFS.begin();//open file-system

	MyWifi::setup();
	MyOta::setup(my_ota_password, my_ota_password);

	tallySystem.setup();
}

void loop() {
	MyOta::loop();
	tallySystem.loop();
}