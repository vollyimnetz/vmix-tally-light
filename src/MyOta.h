#pragma once
#include <Arduino.h>

void myOtaSetup(char* esp_hostname, char* ota_password);
void myOtaLoop();

class MyOta {
public:
    static void setup(char* esp_hostname, char* ota_password);
    static void loop();
};