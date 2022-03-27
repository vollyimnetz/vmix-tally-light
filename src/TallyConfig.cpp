#include "TallyConfig.h"

#include <Arduino.h>
#include <EEPROM.h>

TallyCfgObj cfg;

TallyCfgObj getTallyConfig() {
    return cfg;
}

TallyCfgObj loadTallyConfig() {
    // Loads configuration from EEPROM into RAM
    EEPROM.begin(4095);
    EEPROM.get( 0, cfg );
    EEPROM.end();

    if(cfg.valid!=1) {
        Serial.println("[SET] defaults");
        cfg.valid = 1;
        strcpy(cfg.tallyHost, "http://192.168.178.123");
        strcpy(cfg.tallyKey, "0e1c08d9-e872-4a78-ac99-2d35b2b0ada5");
    }
    Serial.printf("[LOAD] valid: %i\n\r", cfg.valid);
    Serial.printf("[LOAD] tallyHost: %s\n\r", cfg.tallyHost);
    Serial.printf("[LOAD] tallyKey: %s\n\r", cfg.tallyKey);
    return getTallyConfig();
}

void saveTallyConfig() {
    EEPROM.begin(4095);
    cfg.valid = 1;
    EEPROM.put( 0, cfg );
    Serial.printf("[SAVE] valid: %i\n\r", cfg.valid);
    Serial.printf("[SAVE] tallyHost: %s\n\r", cfg.tallyHost);
    Serial.printf("[SAVE] tallyKey: %s\n\r", cfg.tallyKey);
    delay(200);
    EEPROM.commit();                      // Only needed for ESP8266 to get data written
    EEPROM.end();  
}

void eraseTallyConfig() {
    Serial.println("TEST eraseTallyConfig");
    // Reset EEPROM bytes to '0' for the length of the data structure
    EEPROM.begin(4095);
    for (int i = 0 ; i < sizeof(cfg) ; i++) {
        EEPROM.write(i, 0);
    }
    delay(200);
    EEPROM.commit();
    EEPROM.end();
}