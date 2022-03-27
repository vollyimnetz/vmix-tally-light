#pragma once
#include <Arduino.h>


void setupTallySystem(char* settings_password);
void handleClient_TallyLight();


void webserver_handleOther();
int hexcolorToInt(char upper, char lower);
void setTally(String value);
void doWarning(String value);
void doMinor(String value);
bool webserver_loadFromLittleFS(String path);