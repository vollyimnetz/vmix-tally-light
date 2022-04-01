#include "TallyConfig.h"

#include <Arduino.h>
#include <EEPROM.h>


void TallyCfg::save(TallyCfgObj data) {
    EEPROM.begin(4095);
    data.valid = 1;
    EEPROM.put( 0, data );
    Serial.printf("[SAVE] valid     : %i\n\r", data.valid);
    Serial.printf("[SAVE] mode      : %i\n\r", data.mode);
    Serial.printf("[SAVE] tallyHost : %s\n\r", data.tallyHost);
    Serial.printf("[SAVE] tallyKey  : %s\n\r", data.tallyKey);
    delay(200);
    EEPROM.commit();                      // Only needed for ESP8266 to get data written
    EEPROM.end();  
}
TallyCfgObj TallyCfg::get() {
    TallyCfgObj data;
    // Loads configuration from EEPROM into RAM
    EEPROM.begin(4095);
    EEPROM.get( 0, data );
    EEPROM.end();

    if(data.valid!=1) {
        Serial.println("[SET] defaults");
        data.valid = 1;
        data.mode = 0;
        strcpy(data.tallyHost, "http://192.168.178.123");
        strcpy(data.tallyKey, "0e1c08d9-e872-4a78-ac99-2d35b2b0ada5");
    }
    Serial.printf("[LOAD] valid     : %i\n\r", data.valid);
    Serial.printf("[LOAD] mode      : %i\n\r", data.mode);
    Serial.printf("[LOAD] tallyHost : %s\n\r", data.tallyHost);
    Serial.printf("[LOAD] tallyKey  : %s\n\r", data.tallyKey);
    return data;
}
void TallyCfg::doErase() {
    Serial.println("TallyCfg erase");
    // Reset EEPROM bytes to '0' for the length of the data structure
    EEPROM.begin(4095);
    for (unsigned int i = 0 ; i < sizeof(TallyCfgObj) ; i++) {
        EEPROM.write(i, 0);
    }
    delay(200);
    EEPROM.commit();
    EEPROM.end();
}