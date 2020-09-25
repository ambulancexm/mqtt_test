#include <stdlib.h>
#include "constante.h"
#include <string.h>
#include "util.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;


class configWifi
{
  private: 
    char* ssid;
    char* pwd;
    char* mqqt_broker;
    int numWifi;
    char* ip;
    char* mac;
    
  
  public:
    static int nbWifi ;
    static long cpt;

    configWifi(char* _ssid,char* _pwd, char* _mqqt_broker);
    configWifi(char* _ssid,char* _pwd);
    configWifi();
    char* getAP();
    char* getSsid();
    char* getPwd();
    char* getMqqt_broker();
    char* getNumWifi();
    void setIp(String ip);
    void setMac(String mac);
    void setIp(char * ip);
    void setMac(char* mac);
    char* getIp();
    char* getMac();
    void switchWifi();
    void runWifi();
    
};

int configWifi::nbWifi = 0;
long configWifi::cpt= 0;
configWifi::configWifi(char* _ssid,char* _pwd,char* _mqqt_broker){
  nbWifi++;
  numWifi= nbWifi;
  ssid = _ssid;
  pwd = _pwd;
  mqqt_broker = _mqqt_broker;
}

configWifi::configWifi(char* _ssid,char* _pwd){
  nbWifi++;
  numWifi= nbWifi;
  ssid = _ssid;
  pwd = _pwd;
}


configWifi::configWifi(){
  nbWifi++;
}

 

char* configWifi::getAP(){
  char rt[255];
  strcpy(rt,ssid);
  strcat(rt,";");
  strcat(rt,pwd);
  strcat(rt,";");
  strcat(rt,mqqt_broker);
  strcat(rt,";");
  strcat(rt,getNumWifi());
  strcat(rt,";");
  
  return rt;
}
// ip
char* configWifi::getIp(){
  return this->ip;
}

void configWifi::setIp(String ip){
  this->ip = stringToChar(ip);
}

void configWifi::setIp(char * ip){
  this->ip = ip;
}

//mac
char* configWifi::getMac(){
  return this->mac;
}
void configWifi::setMac(String mac){
  this->mac = stringToChar(mac);
}
void configWifi::setMac(char * mac){
  this->mac = mac;
}





char* configWifi::getSsid(){
  return ssid;
}

char* configWifi::getPwd(){
  return pwd;
}

char* configWifi::getMqqt_broker(){
  return mqqt_broker;
}

char* configWifi::getNumWifi(){
  char buffer[5];
  strcpy(buffer,"");
  //iota(1,buffer,10);
  sprintf(buffer, "%d", numWifi);
  return buffer;
}


long fonctionSeule(){
  return configWifi::cpt;
}


void configWifi::switchWifi(){
  
}

void configWifi::runWifi(){
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connecting Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    char _ip[20];
    char _mac[25];
 
  strcpy(_ip,stringToChar(WiFi.localIP().toString()));
  strcpy(_mac,stringToChar(WiFi.macAddress()));

  setIp(_ip);
  setMac(_mac);
    // char str[13];
    // strcpy(str,WiFi.localIP());
    // setIp(WiFi.localIP().toString());
    // setMac(WiFi.macAddress());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(getIp());
    Serial.println(getMac());

    // Serial.println(WiFi.localIP());
    // Serial.println(WiFi.macAddress());

  }
}