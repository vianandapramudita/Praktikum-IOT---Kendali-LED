#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <stdlib.h>
 
// Connect to the WiFi
const char* ssid = "Rubiyah";
const char* password = "33333333";
const char* mqtt_server = "riset.revolusi-it.com";

const char* topik = "iot/kendali";
 
WiFiClient espClient;
PubSubClient client(espClient);
String messages,messages2;
 
void callback(char* topic, byte* payload, unsigned int length) {

 Serial.print("Pesan dari MQTT [");
 Serial.print(topic);
 Serial.print("] ");
 messages="";
 for (int i=0;i<length;i++) { // susun jadi string saja...
  char receivedChar = (char)payload[i]; 
  messages=messages+(char)payload[i]; // ambil pesannya masukkan dalam string
  }
 
  Serial.println(messages);
  messages2="Pesan dari Client";
  char attributes[100];
  messages2.toCharArray(attributes, 100);
}
 
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Menghubungkan diri ke MQTT Server : "+(String)mqtt_server);
 // Attempt to connect
 if (client.connect("G.211.19.0117")) { 
  Serial.println("connected");
  // ... and subscribe to topic
  client.subscribe(topik);
 } else {
  Serial.print("failed, rc=");
  Serial.print(client.state());
  Serial.println(" coba lagi dalam 5 detik...");
  // Wait 5 seconds before retrying
  delay(5000);
  }
 }
}


void konek_wifi()
{
WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
}

 // ------------------------------- begin --------------------------------------- //
void setup()
{
 Serial.begin(9600);
 
 client.setServer(mqtt_server, 1883);
 client.setCallback(callback);
pinMode (D1, OUTPUT);
pinMode (D2, OUTPUT);
pinMode (D3, OUTPUT);
}
 
void loop()
{

 if(WiFi.status() != WL_CONNECTED) { konek_wifi(); } // jika tidak konek wifi maka di reconnect
 if (!client.connected()) { reconnect(); } // reconnect apabila belum konek 
 
 client.loop();
 
}