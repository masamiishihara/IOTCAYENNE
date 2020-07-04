#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include<DHT.h>

#define LED D1
#define LED1 D2
#define DHTpin D3
#define DHTTYPE DHT11
char ssid[] ="Unifique_WIFI_342897";
char wifiPassword[]= "74519036";

//Cayenne authentication info.
char username[] = "d7533cb0-ab19-11ea-883c-638d8ce4c23d";
char password[] = "105f0557171ce9b2b6a74db7b8e4e5f383d1c7d7";
char clientID[] = "5d30d2d0-ae57-11ea-b767-3f1a8f1211ba";
//int LED = 16;

DHT dht(DHTpin,DHTTYPE);
void setup() {
  Serial.begin(9600);
  
  Cayenne.begin(username,password,clientID,ssid,wifiPassword);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  delay(20);
}

void loop() 
{
  Cayenne.loop();
  //publishData();
  delay(3000);
}
//void publishData()
//{
//  int myval = random(0,100);
  //Cayenne.virtualWrite(V0,myval);
//}

CAYENNE_IN(V1)
{
  Serial.print("V1 = ");
  Serial.println(getValue.asInt());
  if(getValue.asInt() == 0)
  {
    digitalWrite(LED,LOW);
  }
  else
  {
    digitalWrite(LED,HIGH);
  }
}
CAYENNE_IN(V2)
{
  Serial.print("V2 = ");
  Serial.println(getValue.asInt());
  if(getValue.asInt() == 0)
  {
    digitalWrite(LED1,LOW);
  }
  else
  {
    digitalWrite(LED1,HIGH);
  }
}
CAYENNE_OUT(V3)
{
  float h = dht.readHumidity();
  delay(3000);
  Serial.print("Umidade = ");
  Serial.println(h);
  if(isnan(h))
  {
    Serial.println("Erro ao ler dados de umidade");
  }
  else
  {
    Cayenne.virtualWrite(V3,h);
  }
}
CAYENNE_OUT(V0)
{
  float t = dht.readTemperature();
  delay(500);
  Serial.print("Temperatura = ");
  Serial.println(t);
  if(isnan(t))
  {
    Serial.println("Erro ao ler dados de temperatura");
  }
  else
  {
  Cayenne.virtualWrite(V0,t);
  }
}