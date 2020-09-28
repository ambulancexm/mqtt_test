#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h> //Librairie pour la gestion Mqtt
#include <stdlib.h>
#include "config_wifi.h"
#include "configIOT.h"
#include "constante.h"
#include "data.h"
#include "iot.h"
#include "meshFile.h"

long tps = 0;
bool tmp = 0;
long nb = 0;
char wifiMac[20];
int cpt = 0;
#define MSG_BUFFER_SIZE 50

  unsigned long lastMsg = 0;
  char msg[MSG_BUFFER_SIZE];
// WiFiClient espClient;
// PubSubClient client(espClient);

Data *datas[10];
configWifi *configWifis[10];

configWifi* homeWifi = new configWifi(ssid, password);
// configIot* iot = new configIot();
// void initDataDevice(){
  
//   configWifis[0] = new configWifi("raspapweb-gui", "ChangeMe", "10.3.43.109");
//   configWifis[1] = new configWifi("thomas", "tiliatilia", "192.168.43.109");
// }


void setup()
{
  Serial.begin(115200);
  homeWifi->runWifi(ssid,password);
  // iot->runIot();
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
// if (!client.connected())
//   {
//     char foo[25];
//     strcpy(foo,homeWifi->getMac());
//     setup_mqtt(foo);
   
//   }
//   client.loop();

  // Serial.println("fin");

  // Serial.print("test retour de data :");
  // //Serial.println(datas[0]->getName());

  // char info[255];
  // reconnect();
  // client.loop();
  // //On utilise pas un delay pour ne pas bloquer la réception de messages
  // if (millis() - tps > 10000)
  // {
  //   tps = Serial.print("str :" );
  // Serial.println(tmp); 1;
  //   tmp = !tmp;
  //   //mqtt_publish("pub/1ab",temp);
  //   mqtt_publish("pub/13ab", tmp);
  // }
  // // strcpy(info, "");
  // // strcat(info, configWifis[0]->getAP());

  // client.publish("loc/tmpTest", "info");
  // nb++;
  // //strcpy(info,"");
  // delay(1500);
}


