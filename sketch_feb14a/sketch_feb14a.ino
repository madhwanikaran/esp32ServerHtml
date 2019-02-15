

#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include "ESPAsyncWebServer.h"

const char* htmlfile = "/index.html";

const char *ssid = "ssidKaran";
const char *password = "";
const int ledPin = 4;
AsyncWebServer server(80);

String ledState;
String ledState2;


String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}

String processor2(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(22)){
      ledState2 = "ON";
    }
    else{
      ledState2 = "OFF";
    }
    Serial.print(ledState2);
    return ledState2;
  }
  return String();
}


 



void setup() {
  delay(1000);
  Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    pinMode(22, OUTPUT);

  Serial.println();

  //Initialize File System
  SPIFFS.begin();
  Serial.println("File System Initialized");

  //Initialize AP Mode
  WiFi.softAP(ssid);  //Password not used
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Web Server IP:");
  Serial.println(myIP);

  //Initialize Webserver
   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
    server.on("/on",HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/off",HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
   server.on("/on2",HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(22, HIGH);    
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });
  server.on("/off2",HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(22, LOW);    
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/prerequist.png", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/prerequist.png", "image/png");
  });
  

  server.begin();  
}

void loop() {
 //server.handleClient();
}
