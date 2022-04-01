#pragma once
#include <Arduino.h>
#include "TallyConfig.h"


class TallySystem {
public:
    TallySystem(char* settings_password);
    void setup();
    void loop();
private:
    TallyCfgObj cfg;
    char* settings_password;
    /*
    void sendTallyRequest(String url);
    //void doTallyResponseCallback(void* optParm, AsyncHTTPRequest* request, int readyState);
    void doWarning(String value);
    void doMinor(String value);
    void setTally(String value);
    bool webserver_loadFromLittleFS(String path);
    void webserver_handleOther();
    */
};

int hexcolorToInt(char upper, char lower);
