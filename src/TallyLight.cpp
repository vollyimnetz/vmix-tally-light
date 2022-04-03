#include "TallyLight.h"
#include <FastLED.h>    //for LED
#define FASTLED_FORCE_SOFTWARE_SPI//for LED
#define FASTLED_INTERNAL//disable pragma message

int hexcolorToInt(char upper, char lower) {
    int uVal = (int) upper;
    int lVal = (int) lower;
    uVal = uVal > 64 ? uVal - 55 : uVal - 48;
    lVal = lVal > 64 ? lVal - 55 : lVal - 48;
    uVal = uVal << 4;
    return uVal + lVal;
}

CRGB ledStripe[LED_STRIP_NUM_LEDS];

TallyLight::TallyLight() {
    Serial.println("---- SETUP FASTLED ----");
    FastLED.addLeds<LED_STRIP_TYPE, LED_STRIP_DATA_PIN>(ledStripe, LED_STRIP_NUM_LEDS);
    FastLED.setBrightness(128);
}

void TallyLight::setColor_full(String value) {
    int ledBrightness = 128;
    value.toUpperCase();
    Serial.println("setColor_full: " + value);

    unsigned int color_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    unsigned int color_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    unsigned int color_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    Serial.print("R: ");Serial.println(color_R);
    Serial.print("G: ");Serial.println(color_G);
    Serial.print("B: ");Serial.println(color_B);

    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(color_R, color_G, color_B);
    }
    FastLED.setBrightness(ledBrightness);
    //delay(200);
    FastLED.show();
    FastLED.show();
    FastLED.show();
}


void TallyLight::setColor_firstOnly(String value) {
    value.toUpperCase();
    Serial.println("setColor_firstOnly: " + value);
    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(0, 0, 0);
    }

    unsigned int color_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    unsigned int color_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    unsigned int color_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    Serial.print("R: ");Serial.println(color_R);
    Serial.print("G: ");Serial.println(color_G);
    Serial.print("B: ");Serial.println(color_B);
    
    ledStripe[ LED_STRIP_NUM_LEDS-1 ].setRGB(color_R, color_G, color_B);
    FastLED.setBrightness(128);
    //delay(200);
    FastLED.show();
    FastLED.show();
    FastLED.show();
}

void TallyLight::setColor_lastOnly(String value) {
    value.toUpperCase();
    Serial.println("setColor_lastOnly: "+value);
    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(0, 0, 0);
    }

    unsigned int color_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    unsigned int color_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    unsigned int color_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    Serial.print("R: ");Serial.println(color_R);
    Serial.print("G: ");Serial.println(color_G);
    Serial.print("B: ");Serial.println(color_B);
    
    ledStripe[ 0 ].setRGB(color_R, color_G, color_B);
    FastLED.setBrightness(64);
    //delay(200);
    FastLED.show();
    FastLED.show();
    FastLED.show();
}