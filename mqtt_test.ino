#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h> //Librairie pour la gestion Mqtt
#include <stdlib.h>
#include "config_wifi.h"
#include "configIOT.h"
#include "data.h"
#include "iot.h"

long tps = 0;
bool tmp = 0;
long nb = 0;
char wifiMac[20];
int cpt = 0;
#define MSG_BUFFER_SIZE 50

  unsigned long lastMsg = 0;
  char msg[MSG_BUFFER_SIZE];


Data *datas[10];
configWifi *configWifis[10];

configWifi* homeWifi = new configWifi("thomas", "tiliatilia");

void setup()
{
  Serial.begin(115200);
  homeWifi->runWifi();
  
  char foo[25];
  strcpy(foo,homeWifi->getMac());
  setup_mqtt(foo);
  
}


void loop()
{
  client.loop();
  unsigned long now = millis();

  if (now - lastMsg > 2000)
  {
    snprintf(msg, MSG_BUFFER_SIZE, "%d", cpt);
    lastMsg = now;
    
    client.publish("temp/test", msg);
    client.publish("loc/tmpTest", "info");
    client.publish("test", "test");
    cpt++;
  }

}


