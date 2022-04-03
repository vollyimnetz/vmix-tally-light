#pragma once
#include <Arduino.h>
#include "settings.h"

int hexcolorToInt(char upper, char lower);

class TallyLight {
public:
    TallyLight();
    void setColor_full(String value);
    void setColor_firstOnly(String value);
    void setColor_lastOnly(String value);
};