

/*
 Basic ESP8266 MQTT example
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.
 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/
#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#define LIGHT 13
#define SPEEDMOTOR 20
#define ONE_WIRE_BUS D2
#define DOORBELL D3
int etatBouton = 1;

//config température dallas
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char *ssid = "NETGEAR51";
const char *password = "livelylotus015";
const char *mqtt_server = "176.166.1.64";
const char *iotName ="sonettePortail";
const char *gps ="garnerans";


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
static int value = 0;

void setup_wifi()
{
  
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  //sprintf(str,"number #%d",value);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println(strcmp(topic,"portier"));
  if(strcmp(topic,"portier") == 0){
    Serial.print(topic);
    
  }

  
}

void reconnect()
{
  char topic[50];
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("openIot", createTopic(topic));
      // ... and resubscribe
      client.subscribe("inTopic");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char* createTopic(char *topic){
  char str[50];
  strcpy(str,gps);
  strcat(str,"/");
  strcat(str,iotName);
  strcpy(topic,str);
}

void sonnette(int pin){
  char str[50];
  
    
  if (digitalRead(pin) == 1 && etatBouton == 0 ){
    sprintf(str,"%d",1);
    client.publish("action/sonnette", str);
    etatBouton = 1;
    Serial.println("marche");
    delay(100);
  }
  if (digitalRead(pin) == 0){
    sprintf(str,"%d",0);
    client.publish("action/sonnette", str);
    Serial.println("arret");
    etatBouton = 0;
    delay(100);
  }
}

void setup()
{
  sensors.begin();
  pinMode(DOORBELL,INPUT_PULLUP);
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  char str[50];
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
//  sensors.requestTemperatures();
//  unsigned long now = millis();
//  double temp = sensors.getTempCByIndex(0);
//  //temp = (temp-32)*5/9;
//  
//  if (now - lastMsg > 2000)
//  {
//    lastMsg = now;
//    ++value;
//    snprintf(msg, MSG_BUFFER_SIZE, "%2lf", temp);
//    Serial.print("Publish message: ");
//    Serial.println(temp);
//    sprintf(str,"number #%d",value);
//    client.publish("temp", msg);
//    sprintf(str,"%d",99);
//    client.publish("ping",str);
//   
//  }
    sonnette(DOORBELL);
}
