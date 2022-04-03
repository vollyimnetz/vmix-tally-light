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
    void handleResult(String result);
};

int hexcolorToInt(char upper, char lower);
