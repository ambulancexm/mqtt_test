#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LIGHT 13
#define SPEEDMOTOR 20
#define ONE_WIRE_BUS D2

//config température dallas
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char *ssid = "LDNR-1019";
const char *password = "Jai1ClioRougeDansLeGarage";
const char *mqtt_server = "192.168.10.195";


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
static int value = 0;
int baseTemp = 5;

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
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

    

  if (strcmp(topic,"retour/congel") == true ){
    baseTemp = (int)payload[0];
  }
}

void reconnect()
{
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
      client.publish("outTopic", "hello world");
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

void marcheArret(double temp){
  //if(temp > baseTemp && temp < 
}

void setup()
{
  sensors.begin();
  pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  client.subscribe("retour/congel");
  char str[50];
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  sensors.requestTemperatures();
  unsigned long now = millis();
  double temp = sensors.getTempCByIndex(0);
  //temp = (temp-32)*5/9;
  
  if (now - lastMsg > 2000)
  {
    lastMsg = now;
    
    snprintf(msg, MSG_BUFFER_SIZE, "valeur %.2f", temp);
    Serial.print("Publish message: ");
    Serial.println(msg);
    sprintf(str,"number #%d",value);
    client.publish("temp", msg);
    snprintf(msg, MSG_BUFFER_SIZE, "valeur %d", analogRead(A0));
    client.publish("hydro",msg);
  }
}
