#include <stdlib.h>

class configWifi
{
  private: 
    char* ssid;
    char* pwd;
    char* mqqt_broker;
    int numWifi;
  
  public:
    static int nbWifi ;

    configWifi(char* _ssid,char* _pwd, char* _mqqt_broker);
    char* getAP();
    char* getSsid();
    char* getPwd();
    char* getMqqt_broker();
    char* getNumWifi();
    
    
};

configWifi::configWifi(char* _ssid,char* _pwd,char* _mqqt_broker){
  nbWifi++;
  numWifi= nbWifi;
  ssid = _ssid;
  pwd = _pwd;
  mqqt_broker = _mqqt_broker;
}

 int configWifi::nbWifi = 0;

char* configWifi::getAP(){
  char rt[255];
  strcat(rt,ssid);
  strcat(rt,";");
  strcat(rt,pwd);
  strcat(rt,";");
  strcat(rt,mqqt_broker);
  strcat(rt,";");
  strcat(rt,getNumWifi());
  strcat(rt,";");
  
  return rt;
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
