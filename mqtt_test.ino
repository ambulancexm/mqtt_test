#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h> //Librairie pour la gestion Mqtt
#include <stdlib.h>
#include "config_wifi.h"
#include "configIOT.h"
#include "data.h"
#include "iot.h"
#include <ArduinoOTA.h>
//#include "upload.h"
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
  // setupUpload();
  // upload test
    Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  homeWifi->runWifi();
  
  char foo[25];
  strcpy(foo,homeWifi->getMac());
  setup_mqtt(foo);
  
}


void loop()
{
  ArduinoOTA.handle();
  //loopUpload();
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


