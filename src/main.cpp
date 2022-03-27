#include "settings.h"
#include <Arduino.h>
#include <LittleFS.h>
#include "OtaSetup.h"
#include "WifiSetup.h"
#include "TallySystem.h"

char my_ota_password[] = OTA_PASS;
char my_esp_hostname[] = ESP_HOSTNAME;

void setup() {
	Serial.begin(115200);
	delay(500);
	LittleFS.begin();//open file-system

	myWifiSetup();
	myOtaSetup(my_ota_password, my_ota_password);

	setupTallySystem(my_ota_password);
}

void loop() {
	myOtaLoop();
	handleClient_TallyLight();
}