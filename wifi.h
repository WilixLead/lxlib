#ifndef __LXLIB_WIFI__
#define __LXLIB_WIFI__

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "lxlib-config.h"

struct station {
  String ssid;
  String password;
};

extern ESP8266WebServer httpServer;
extern int stationIterator;
extern station knownStations[];

#define ON_WIFI_CONNECTING() 0;
#define ON_WIFI_CONNECTED() 0;
#define ON_WIFI_DISCONNECTED() 0;

void initWiFi();
void loopWiFi();
void connectToWiFi();
String macToString(const unsigned char* mac);

#endif