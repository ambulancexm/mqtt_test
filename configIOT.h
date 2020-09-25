#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h> //Librairie pour la gestion Mqtt
// #include "constante.h"

class configIot
{
    static WiFiClient espClient;
    static PubSubClient client(WiFiClient espClient);
    private:
        char * name;
        char * mqttServer;
        int mqttPort;
        void setup_mqtt();
        void callback(char *topic, byte *payload, unsigned int length);
        void reconnect();
    public:
      
        configIot();
        void runIot();

};

configIot::configIot(){
    name =  nameIot;
    mqttServer = mqtt_server;
    mqttPort = portIot;
}

void configIot::runIot(){
    // WiFiClient espClient;
    // PubSubClient client(espClient);

}

void configIot::setup_mqtt()
{
  client.setServer(mqtt_server, mqttPort);
  client->setCallback(callback); //Déclaration de la fonction de souscription
  reconnect();
}

//Callback doit être présent pour souscrire a un topic et de prévoir une action
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("-------Nouveau message du broker mqtt-----");
  Serial.print("Canal:");
  Serial.println(topic);
  Serial.print("donnee:");
  Serial.write(payload, length);
  Serial.println();
  if (topic == "sensor/temperature")
  {
    Serial.println("reception ok sensor ");
  }

  if ((char)payload[0] == '1')
  {
    Serial.println("LED ON");
    digitalWrite(13, HIGH);
  }
  else
  {
    Serial.println("LED OFF");
    digitalWrite(13, LOW);
  }
}

void configIot::reconnect()
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
  client.subscribe("sensor/temperature"); //souscription au topic led pour commander une led
  client.subscribe("pub/13a");
}


