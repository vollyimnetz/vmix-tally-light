#include "MyWifi.h"

#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <Ticker.h>

void MyWifi::setup() {
  //set led pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  // start ticker with 0.5 because we start in AP mode and try to connect
  Ticker ticker;
  ticker.attach(0.6, []() {
    //toggle state
    int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
    digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
  });


  WiFiManager wifiManager;
  //char wifi_esp_hostname[] = ESP_HOSTNAME;
  //wifiManager.setHostname(wifi_esp_hostname);//not yet implemented

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "EspAutoWifi"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("EspAutoWifi")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();
  //turn LED off
  digitalWrite(LED_BUILTIN, HIGH);
}