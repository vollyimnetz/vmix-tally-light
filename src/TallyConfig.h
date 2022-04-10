#pragma once
#include <Arduino.h>

struct TallyCfgObj {
    bool valid;                       // 0=no configuration, 1=valid configuration
    int mode;
    char tallyHost[80];               // Host of vmix
    char tallyKey[80];                // tally system key
};

class TallyCfg {
    public: static void save(TallyCfgObj data);
    public: static TallyCfgObj get();
    public: static void doErase();
};