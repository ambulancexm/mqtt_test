#include <stdlib.h>
#include "constante.h"
#include <string.h>
#include "util.h"



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
    configWifi();
    char* getAP();
    char* getSsid();
    char* getPwd();
    char* getMqqt_broker();
    char* getNumWifi();
    void setIp(String ip);
    void setMac(String mac);
    char* getIp();
    char* getMac();
    
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
  Serial.print("dans le getter : ");
  Serial.println(this->ip);
  return this->ip;
}

void configWifi::setIp(String ip){
  this->ip = stringToChar(ip);
}

//mac
char* configWifi::getMac(){
  return this->mac;
}
void configWifi::setMac(String mac){
  this->mac = stringToChar(mac);
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



