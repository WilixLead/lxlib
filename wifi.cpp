
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "wifi.h"

IPAddress AP_local_IP(AP_IP);
IPAddress AP_gateway(AP_GATEWAY);
IPAddress AP_subnet(AP_SUBNET);
int stationIterator = 0;
station knownStations[] = KNOWN_STATIONS;

ESP8266WebServer httpServer(HTTP_SERVER_PORT);

void handleRoot() {
  if (httpServer.args() > 0) {
    int step = 0;
    String essid;
    String password;
    for (uint8_t i = 0; i < httpServer.args(); i++) {
      if (httpServer.argName(i) == "essid") {
        essid = httpServer.arg(i);
        step++;
      }
      if (httpServer.argName(i) == "password") {
        password = httpServer.arg(i);
        step++;
      }
    }
    if (step >= 2) {
      WiFi.begin(essid, password);
    }
  }
  String page = 
  "<html>\
    <head>\
      <title>WiFi Configurator</title> \
    </head>\
    <body>\
      <form method=\"GET\">\
        <label>ESSID</label>\
        <input type=\"text\" name=\"essid\" />\
        <br/>\
        <label>PASSWORD</label>\
        <input type=\"text\" name=\"password\" />\
        <br/>\
        <br/>\
        <input type=\"submit\" value=\"Connect\" />\
      </form>\
      <p></p>\
      <p>Device name: " + String(HOST_NAME) + "\
      <p>VCC: " + String(ESP.getVcc()) + "\
    </body>\
  </html>";

  httpServer.send(200, "text/html", page);
}

void handleState() {
  String json = "{\
    \"vcc\": \"" + String(ESP.getVcc()) + "\"\
  }";
  httpServer.send(200, "application/json", json);
}

void onStationConnected(const WiFiEventStationModeConnected& evt) {
  Serial.print("Connected to ");
  Serial.println(evt.ssid);
}

void onGotIP(const WiFiEventStationModeGotIP& evt) {
  Serial.print("IP address: ");
  Serial.println(evt.ip);
  Serial.print("Gateway: ");  
  Serial.println(evt.gw);
  ON_WIFI_CONNECTED();
}

void onStationDisconnected(const WiFiEventStationModeDisconnected& evt) {
  Serial.print("WiFi disconnected");
  // if (WiFi.softAPgetStationNum() > 0) {
  //   return;
  // }
  ON_WIFI_DISCONNECTED();
  stationIterator++;
  if (stationIterator >= KNOWN_STATIONS_LENGTH) {
    stationIterator = 0;
  }
  connectToWiFi();
}

void connectToWiFi() {
  //Connect to wifi Network
  Serial.print("Connecting to WIFI: "); 
  Serial.print(knownStations[stationIterator].ssid);
  Serial.print(" with password: "); 
  Serial.println(knownStations[stationIterator].password);
  WiFi.begin(knownStations[stationIterator].ssid, knownStations[stationIterator].password);
  Serial.print("After connect begin"); 
  ON_WIFI_CONNECTING();
}

void initWiFi() {
  WiFi.hostname(HOST_NAME);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);
  WiFi.onStationModeConnected(&onStationConnected);
  WiFi.onStationModeDisconnected(&onStationDisconnected);
  WiFi.onStationModeGotIP(&onGotIP);
  WiFi.onSoftAPModeStationDisconnected([](const WiFiEventSoftAPModeStationDisconnected) {
    if (WiFi.softAPgetStationNum() <= 0) {
      stationIterator = 0;
      connectToWiFi();
    }
  });
  
  WiFi.mode(WIFI_AP_STA);
  connectToWiFi();
  WiFi.softAP(AP_SSID, AP_PWD);
  WiFi.softAPConfig(AP_local_IP, AP_gateway, AP_subnet);

  httpServer.on("/", handleRoot);
  httpServer.on("/state", handleState);
  httpServer.begin();
}

void loopWiFi() {
  httpServer.handleClient();
}

String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}