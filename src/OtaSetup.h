#pragma once
#include <Arduino.h>

void myOtaSetup(char* esp_hostname, char* ota_password);
void myOtaLoop();