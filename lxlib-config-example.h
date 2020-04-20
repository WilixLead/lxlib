#ifndef __LXLIB_CONFIG_H__
#define __LXLIB_CONFIG_H__

#define HOST_NAME "WiBrick0002"

#define HTTP_SERVER_PORT 80
#define AP_SSID HOST_NAME
#define AP_PWD "12345678"
#define AP_IP 192,168,1,1
#define AP_GATEWAY 192,168,1,1
#define AP_SUBNET 255,255,255,0

#define OTA_HOST AP_SSID // You can have different host name for OTA
/**
 * Hash your password with MD5 and place to next line
 */
#define OTA_PWD "81dc9bdb52d04dc20036dbd8313ed055" // - 1234

#define KNOWN_STATIONS_LENGTH 1
#define KNOWN_STATIONS {\
  { "my-wifi-essid-name", "my-wifi-password" },\
};

#endif