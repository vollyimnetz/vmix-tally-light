#include "TallySystem.h"
#include "TallyLight.h"

#include <AsyncHTTPRequest_Generic.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>   // Include the LittleFS library


ESP8266WebServer server(80);

//#define _ASYNC_HTTP_LOGLEVEL_     2
AsyncHTTPRequest tallyRequest;


bool runTally = true;
bool hasOpenRequest = false;
String currentValue = "000000";
TallyLight light;

void sendTallyRequest(String url) {
    static bool requestOpenResult;

    if(hasOpenRequest) {
        Serial.println("Skip cause request is open");
        return;
    } 
    hasOpenRequest = true;
    
    url = url+"&state=%23"+currentValue;
    if (tallyRequest.readyState() == readyStateUnsent || tallyRequest.readyState() == readyStateDone) {
        requestOpenResult = tallyRequest.open("GET", url.c_str());
        
        if (requestOpenResult) {
            // Only send() if open() returns true, or crash
            tallyRequest.send();
            Serial.println("Open request: "+url);
        } else {
            Serial.println("Can't send - bad request");
            delay(5000);//wait for 5 seconds
            hasOpenRequest = false;
        }
    } else {
        hasOpenRequest = false;
        //Serial.println("Can't send request");
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
    tallyRequest.onReadyStateChange( [this](void* optParm, AsyncHTTPRequest* request, int readyState) {
        (void) optParm;
        if (readyState == readyStateDone) {
            String result = request->responseText();
            this->handleResult(result);
        }
        request->setDebug(false);
        hasOpenRequest = false;
    } );

    light = TallyLight();

    server.on("/api/restart",[]() { 
        light.setColor_full("000000");
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
    
    if(runTally && !hasOpenRequest) {
        String url = String(this->cfg.tallyHost)+"/tallyupdate/?key="+String(this->cfg.tallyKey);
        sendTallyRequest(url);
    }
    
    server.handleClient();
}

void TallySystem::handleResult(String result) {
    if(result.length()==23) {
        currentValue = result.substring(14,20);
        Serial.println("Tally value found: "+currentValue);

        switch(this->cfg.mode) {
            case 3:
                if(currentValue.equals("ff0000")) {
                    light.setColor_full("00ff00");
                } else {
                    light.setColor_full("000000");
                }
                break;
            case 2:
                if(currentValue.equals("ff0000")) {
                    light.setColor_full(currentValue);
                } else {
                    light.setColor_full("000000");
                }
                break;
            case 1:
                if(currentValue.equals("ff0000")) {
                    light.setColor_full(currentValue);
                } else {
                    light.setColor_lastOnly(currentValue);
                }
                break;
            default:
                light.setColor_full(currentValue);
                break;
        }
    } else {
        currentValue = "000000";
        light.setColor_firstOnly("ff0000");
        Serial.println("UNKOWN CONTENT");
        Serial.println(result);
    }
}