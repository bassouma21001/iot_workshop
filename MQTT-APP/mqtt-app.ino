#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Lolipop";
const char* password =  "test0000";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
String  TEXT = "";
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  pinMode(5,OUTPUT);
  WiFi.begin(ssid, password);
  String clientId = "ESP8266-";
  clientId += String(random(0xffff), HEX);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect(clientId.c_str())) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("IOT/club/issatso", "Hello from ESP8266 Wiwoo");
  client.subscribe("IOT/club");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
      TEXT += (char)payload[i];
  }
  Serial.println();
  Serial.println(TEXT);

  if (TEXT == "OPENLED"){
    Serial.println("open");
    digitalWrite(5,HIGH);
   }
  if (TEXT == "CLOSELED"){
    Serial.println("close");
    digitalWrite(5,LOW);
   }
     TEXT = "";
  Serial.println("-----------------------");

 
}
 
void loop() {
  client.loop();
}
