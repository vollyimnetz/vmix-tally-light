#include "TallySystem.h"
#include "tallyHelper.h"

#include <AsyncHTTPRequest_Generic.h>
#include <ESP8266WebServer.h>
#include <FastLED.h>    //for LED
#include <LittleFS.h>   // Include the LittleFS library


ESP8266WebServer server(80);
AsyncHTTPRequest tallyRequest;

#define FASTLED_FORCE_SOFTWARE_SPI//for LED
#define FASTLED_INTERNAL//disable pragma message

//FastLED
#define LED_STRIP_NUM_LEDS 5// How many leds in your strip?
#define LED_STRIP_DATA_PIN D5
#define LED_STRIP_TYPE NEOPIXEL
int ledBrightness = 255;
CRGB ledStripe[LED_STRIP_NUM_LEDS];// Define the array of leds
unsigned int ledStrip_R = 0;
unsigned int ledStrip_G = 0;
unsigned int ledStrip_B = 0;

bool runTally = true;
bool isRequestOpen = false;
String currentValue = "000000";


void sendTallyRequest(String url) {
    static bool requestOpenResult;
    
    if (tallyRequest.readyState() == readyStateUnsent || tallyRequest.readyState() == readyStateDone) {
        //requestOpenResult = tallyRequest.open("GET", "http://worldtimeapi.org/api/timezone/Europe/London.txt");
        requestOpenResult = tallyRequest.open("GET", url.c_str());
        
        if (requestOpenResult) {
            isRequestOpen = true;
            // Only send() if open() returns true, or crash
            tallyRequest.send();
            Serial.println("Open request: "+url);
        } else {
            Serial.println("Can't send bad request");
        }
    } else {
        Serial.println("Can't send request");
    }
}

void setTally(String value) {
    ledBrightness = 255;
    value.toUpperCase();
    ledStrip_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    ledStrip_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    ledStrip_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    //Serial.print('R: ');Serial.println(ledStrip_R);
    //Serial.print('G: ');Serial.println(ledStrip_G);
    //Serial.print('B: ');Serial.println(ledStrip_B);
    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(ledStrip_R, ledStrip_G, ledStrip_B);
    }
    FastLED.setBrightness(ledBrightness);
    FastLED.show();
}


void doWarning(String value) {
    ledBrightness = 255;
    Serial.println("SHOW WARNING");
    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(0, 0, 0);
    }

    value.toUpperCase();
    ledStrip_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    ledStrip_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    ledStrip_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    
    ledStripe[ LED_STRIP_NUM_LEDS-1 ].setRGB(ledStrip_R, ledStrip_G, ledStrip_B);
    FastLED.setBrightness(ledBrightness);
    FastLED.show();
    FastLED.show();
    FastLED.show();
}

void doMinor(String value) {
    ledBrightness = 64;
    Serial.println("SHOW WARNING");
    for(int i = 0; i < LED_STRIP_NUM_LEDS; i++) {
        ledStripe[i].setRGB(0, 0, 0);
    }

    value.toUpperCase();
    ledStrip_R = hexcolorToInt( value.charAt(0), value.charAt(1) );
    ledStrip_G = hexcolorToInt( value.charAt(2), value.charAt(3) );
    ledStrip_B = hexcolorToInt( value.charAt(4), value.charAt(5) );
    
    ledStripe[ 0 ].setRGB(ledStrip_R, ledStrip_G, ledStrip_B);
    FastLED.setBrightness(ledBrightness);
    FastLED.show();
    FastLED.show();
    FastLED.show();
}


void doTallyResponseCallback(void* optParm, AsyncHTTPRequest* request, int readyState) {
    (void) optParm;
    
    if (readyState == readyStateDone) {
        String result = request->responseText();
        Serial.println( result );
        if(result.length()==23) {
            Serial.print("Tally value found: ");
            Serial.println( result );
            Serial.println( result.substring(14,20) );
            currentValue = result.substring(14,20);
            if(currentValue.equals("ff0000")) {
                setTally(currentValue);
            } else {
                doMinor(currentValue);
            }
        } else {
            currentValue = "000000";
            doWarning("ff0000");
            delay(10000);
            Serial.println("UNKOWN CONTENT");
            Serial.println(result);
        }
        
        isRequestOpen = false;
        request->setDebug(false);
    }
}


//tell the client what to do with data
bool webserver_loadFromLittleFS(String path) {
    LittleFS.begin();//open file-system
    String dataType = "text/plain";
    if (path.endsWith("/")) path += "index.html"; //this is where index.htm is created

    if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".htm")) dataType = "text/html";
    else if (path.endsWith(".html")) dataType = "text/html";
    else if (path.endsWith(".css")) dataType = "text/css";
    else if (path.endsWith(".js")) dataType = "application/javascript";
    else if (path.endsWith(".png")) dataType = "image/png";
    else if (path.endsWith(".gif")) dataType = "image/gif";
    else if (path.endsWith(".jpg")) dataType = "image/jpeg";
    else if (path.endsWith(".ico")) dataType = "image/x-icon";
    else if (path.endsWith(".svg")) dataType = "image/svg+xml";
    else if (path.endsWith(".xml")) dataType = "text/xml";
    else if (path.endsWith(".pdf")) dataType = "application/pdf";
    else if (path.endsWith(".zip")) dataType = "application/zip";

    File dataFile = LittleFS.open(path.c_str(), "r");   //open file to read
    if (!dataFile)  //unsuccesful open
    {
        Serial.print("Don't know this command and it's not a file in LittleFS : ");
        Serial.println(path.c_str());
        return false;
    }
    if (server.hasArg("download")) dataType = "application/octet-stream";
    if (server.streamFile(dataFile, dataType) != dataFile.size()) {}    //a lot happening here

    dataFile.close();

    return true; //shouldn't always return true, Added false above
}

void webserver_handleOther() {
    if(webserver_loadFromLittleFS(server.uri())) return;   //gotcha - it's a file in LittleFS
    String message = "Not Found\n\n";           //or not...
    message += "URI: ";     //make a 404 response & provide debug information
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    }
    server.send(404, "text/plain", message);
    Serial.println(message);
}

String getConfigAsJson(TallyCfgObj cfg) {
    return "{ \"mode\" : "+String(cfg.mode)+", \"host\" : \""+String(cfg.tallyHost)+"\", \"key\" : \""+String(cfg.tallyKey)+"\", \"ip\" : \""+WiFi.localIP().toString()+"\" }";
}


TallySystem::TallySystem(char* settings_password) {
    this->cfg = TallyCfg::get();
    this->settings_password = settings_password;
}

void TallySystem::setup() {
    tallyRequest.onReadyStateChange( doTallyResponseCallback );

    //fastLED LED-Strip setup
    FastLED.addLeds<LED_STRIP_TYPE, LED_STRIP_DATA_PIN>(ledStripe, LED_STRIP_NUM_LEDS);
    FastLED.setBrightness(ledBrightness);


    server.on("/api/restart",[]() { 
        ESP.restart();
        return;
    });
    server.on("/api/stoptally",[]() { 
        runTally = false;
        server.send(200, "application/json", "{ \"result\" : \"OK\" }");
        return;
    });
    server.on("/api/starttally",[]() { 
        runTally = true;
        server.send(200, "application/json", "{ \"result\" : \"OK\" }");
        return;
    });
    server.on("/api/readsettings", [*this]() {
        if(!server.authenticate("tallylight", this->settings_password)) return server.requestAuthentication();
        server.send(200, "application/json", getConfigAsJson(this->cfg));
        return;
    });

    server.on("/api/writesettings", [*this]() {
        TallyCfgObj cfg = this->cfg;
        if(!server.authenticate("tallylight", this->settings_password)) return server.requestAuthentication();
        if(server.arg("mode").length() > 0) {
            cfg.mode = server.arg("mode").toInt();
        }
        if(server.arg("host").length() > 0) {
            strcpy(cfg.tallyHost, server.arg("host").c_str());
        }
        if(server.arg("key").length() > 0) {
            strcpy(cfg.tallyKey, server.arg("key").c_str());
        }
        TallyCfg::save(cfg);
        server.send(200, "application/json", getConfigAsJson(cfg));
        return;
    });
    
    server.onNotFound( webserver_handleOther );
    server.begin();
    //*/
    Serial.println("HTTP server started");
}

void TallySystem::loop() {
    
    if(runTally && !isRequestOpen) {
        String url = String(this->cfg.tallyHost)+"/tallyupdate/?key="+String(this->cfg.tallyKey)+"&state=%23"+currentValue;
        sendTallyRequest(url);
    }
    
    server.handleClient();
}