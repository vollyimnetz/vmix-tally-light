#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <AsyncHTTPRequest_Generic.h>           // https://github.com/khoih-prog/AsyncHTTPRequest_Generic
#include <ESP8266mDNS.h>
#include <FS.h>
#include "settings.h"

ESP8266WebServer server(80);

void setup() {
	Serial.begin(115200);
	delay(500);
	SPIFFS.begin();//open file-system

	myWifiSetup();
	myOtaSetup();

	setupTallySystem();
}

void loop() {
	myOtaLoop();
	doTallyLight();
	server.handleClient();
}