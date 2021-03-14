#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <ArduinoJson.h>
 
class Network
{
private:
   
public:
  void init(String ssid, String password);
  int getWeather(void);
  int getTime(void);

};

#endif
