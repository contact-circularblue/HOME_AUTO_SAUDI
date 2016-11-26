#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

WiFiUDP UDP;
void setup() {
  // put your setup code here, to run once:
String IP ="192,168,205,122";
String a="192";
int i=a.toInt();
Serial.begin(115200);
Serial.println("i =:");
Serial.println(i);


IPAddress ip(i,i,i,i);
UDP.remoteIP()= ip;
while(1)
delay(10);

IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFi.config(ip, gateway, subnet);
}

void loop() {
  // put your main code here, to run repeatedly:

}
