#pragma once
#include <Arduino.h>

struct TallyCfgObj {
    int valid;                        // 0=no configuration, 1=valid configuration
    char tallyHost[80];               // Host of vmix
    char tallyKey[80];                // tally system key
};

TallyCfgObj getTallyConfig();
TallyCfgObj loadTallyConfig();
void saveTallyConfig();
void eraseTallyConfig();