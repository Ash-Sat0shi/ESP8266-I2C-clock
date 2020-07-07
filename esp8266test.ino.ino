#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

void setup() {
  // put your setup code here, to run once:
WiFiManager wifiManager;
//first parameter is name of access point, second is the password
wifiManager.autoConnect("ESP8266test", "test1234");
}

void loop() {
  // put your main code here, to run repeatedly:

}
