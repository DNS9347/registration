#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
const int trigPin1 ='D1';
const int echoPin1 ='D2';
#define redled 'D3'
#define grnled 'D4'
#define Buzz 'D5'
unsigned long ch_no = 1742885;//Replace with Thingspeak Channel number
const char * write_api = "OYETT1WDX6BA14UZ";//Replace with Thingspeak write API
char auth[] = " mwa0000024498553";
char ssid[] = "DNS";
char pass[] = "12345678";
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 10000;
WiFiClient  client;
long duration1;
int distance1;
void setup()
{
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(redled, OUTPUT);
  pinMode(grnled, OUTPUT);
  pinMode(Buzz,OUTPUT);
  digitalWrite(redled, LOW);
  digitalWrite(grnled, LOW);
  digitalWrite(Buzz,HIGH);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  startMillis = millis();  //initial start time
}
void loop()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;
  Serial.println(distance1);
  if (distance1 <= 4)
  {
    digitalWrite('D3', HIGH);
    digitalWrite('D4', LOW);
    digitalWrite('D5',LOW);
  }
  else
  {
    digitalWrite('D4', HIGH);
    digitalWrite('D3', LOW);
    digitalWrite('D5',HIGH);
  }
  currentMillis = millis();
  if (currentMillis - startMillis >= period)
  {
    ThingSpeak.setField(1, distance1);
    ThingSpeak.writeFields(ch_no, write_api);
    startMillis = currentMillis;
  }
}
