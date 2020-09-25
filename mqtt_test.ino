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

// WiFiClient espClient;
// PubSubClient client(espClient);

Data *datas[10];
configWifi *configWifis[10];

configWifi* homeWifi = new configWifi("thomas", "tiliatilia");
// configIot* iot = new configIot();
// void initDataDevice(){
  
//   configWifis[0] = new configWifi("raspapweb-gui", "ChangeMe", "10.3.43.109");
//   configWifis[1] = new configWifi("thomas", "tiliatilia", "192.168.43.109");
// }

// void setup_mqtt()
// {
//   client.setServer(mqtt_server, mqttPort);
//   client.setCallback(callback); //Déclaration de la fonction de souscription
//   reconnect();
// }

// //Callback doit être présent pour souscrire a un topic et de prévoir une action
// void callback(char *topic, byte *payload, unsigned int length)
// {
//   Serial.println("-------Nouveau message du broker mqtt-----");
//   Serial.print("Canal:");
//   Serial.println(topic);
//   Serial.print("donnee:");
//   Serial.write(payload, length);
//   Serial.println();
//   if (topic == "sensor/temperature")
//   {
//     Serial.println("reception ok sensor ");
//   }

//   if ((char)payload[0] == '1')
//   {
//     Serial.println("LED ON");
//     digitalWrite(13, HIGH);
//   }
//   else
//   {
//     Serial.println("LED OFF");
//     digitalWrite(13, LOW);
//   }
// }

// void reconnect()
// {
//   while (!client.connected())
//   {
//     // Serial.println("Connection au serveur MQTT ...");
//     if (client.connect("ESP32Client"))
//     {
//       // Serial.println("MQTT connecté");
//     }
//     else
//     {
//       Serial.print("echec, code erreur= ");
//       Serial.println(client.state());
//       Serial.println("nouvel essai dans 2s");
//       delay(2000);
//     }
//   }
//   client.subscribe("sensor/temperature"); //souscription au topic led pour commander une led
//   client.subscribe("pub/13a");
// }

// //Fonction pour publier un float sur un topic
// void mqtt_publish(String topic, float t)
// {
//   char top[topic.length() + 1];
//   topic.toCharArray(top, topic.length() + 1);
//   char t_char[50];
//   String t_str = String(t);
//   t_str.toCharArray(t_char, t_str.length() + 1);
//   client.publish(top, t_char);
// }


void setup()
{
  Serial.begin(115200);
  homeWifi->runWifi();
  // iot->runIot();
  char foo[25];
  strcpy(foo,homeWifi->getMac());
  setup_mqtt(foo);
  
}
void loop()
{
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


