#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h> //Librairie pour la gestion Mqtt
#include <stdlib.h>
#include "config_wifi.h"
#include "util.h"
#include "configIOT.h"
#include "data.h"

long tps = 0;
bool tmp = 0;
long nb = 0;
char wifiMac[20];
int cpt = 0;
int etat = HIGH;
ESP8266WiFiMulti WiFiMulti;
WiFiClient espClient;
PubSubClient client(espClient);

Data *datas[10];
configWifi *configWifis[10];

void initDataDevice()
{

  // datas[0] = new Data(0);
  // datas[0]->setName("temperature");

  // datas[1] = new Data(1);
  // datas[0]->setName("pression");

  configWifis[0] = new configWifi("raspapweb-gui", "ChangeMe", "10.3.43.109");
  configWifis[1] = new configWifi("thomas", "tiliatilia", "176.166.1.64");
}

// config wifi
void setup_wifi()
{
  int itemWifi = 0;
  // WiFiMulti.addAP(configWifis[0]->getSsid(), configWifis[0]->getPwd());
  //connexion au wifi
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    itemWifi++;
    if (itemWifi == configWifi::nbWifi)
    {
      itemWifi = 0;
    }
    WiFiMulti.addAP(configWifis[itemWifi]->getSsid(), configWifis[itemWifi]->getPwd());
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("MAC : ");
  // convertStrChar(WiFi.macAddress(),wifiMac);
  Serial.println(WiFi.macAddress());

  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void setup_mqtt()
{
  pinMode(BUILTIN_LED, OUTPUT);
  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback); //Déclaration de la fonction de souscription
  reconnect();
}

//Callback doit être présent pour souscrire a un topic et de prévoir une action
void callback(char *topic, byte *payload, unsigned int length)
{
  
  Serial.print("topic : ");
  Serial.println(topic);
  if (strcmp(topic, "pub/test") == 0)
  {
    Serial.print("test reussi : ");
    Serial.println(etat);
    etat = !etat;
    digitalWrite(BUILTIN_LED, etat);
  }
  else
  {
    Serial.println("test pas reussi");
  }
}

void reconnect()
{
  while (!client.connected())
  {
    // Serial.println("Connection au serveur MQTT ...");
    if (client.connect("ESP32Client"))
    {
      // Serial.println("MQTT connecté");
    }
    else
    {
      Serial.print("echec, code erreur= ");
      Serial.println(client.state());
      Serial.println("nouvel essai dans 2s");
      delay(2000);
    }
  }
  // client.subscribe("sensor/temperature"); //souscription au topic led pour commander une led
  // client.subscribe("pub/13a");
}

//Fonction pour publier un float sur un topic
void mqtt_publish(String topic, float t)
{
  char top[topic.length() + 1];
  topic.toCharArray(top, topic.length() + 1);
  char t_char[50];
  String t_str = String(t);
  t_str.toCharArray(t_char, t_str.length() + 1);
  client.publish(top, t_char);
}

// void configIot(char *name, char *ip)
// {
//   char buf[100];
//   strcpy(buf, name);
//   strcat(buf, ";");
//   strcat(buf, ip);
//   strcat(buf, ";");
//   strcat(buf, wifiMac);
//   client.publish("config/name", buf);
// }

void setup()
{
  Serial.begin(9600);
  configWifis[0] = new configWifi("thomas", "tiliatilia", "176.166.1.64");
  // initDataDevice();
  setup_wifi();
  setup_mqtt();
  // Serial.println("rthomas");
}

void loop()
{
  // // Serial.print("test retour de data :");
  // // Serial.println(datas[0]->getName());

  // char info[255];
  reconnect();
  client.loop();
  // //On utilise pas un delay pour ne pas bloquer la réception de messages
  if (millis() - tps > 2000)
  {
    tps = millis();
    float temp = random(30);
    temp = 1;
    tmp = !tmp;
    //mqtt_publish("pub/1ab",temp);
    // mqtt_publish("pub/13ab", tmp);
    client.subscribe("pub/test");
  }

  // // strcpy(info, "");
  // // strcat(info, configWifis[0]->getAP());

  // // client.publish("loc/tmpTest", "info");
  // // nb++;
  // // //strcpy(info,"");
  // // delay(1500);
}