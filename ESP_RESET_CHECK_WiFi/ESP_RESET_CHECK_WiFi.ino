#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>


boolean wifiConnected = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.begin(512);

  ESP.eraseConfig();

  if (EEPROM.read(200) == 1)
  {
    Serial.println("flag=1");
    while (!connectWifi())
      delay(100);

    Serial.println("done");
  }

  void loop() {
    // put your main code here, to run repeatedly:
    EEPROM.write(200, 1);
    delay(10);
  }

  // connect to wifi – returns true if successful or false if not
  boolean connectWifi()
  {
    Serial.print("ESP RESETTING");
    ESP.reset();
  }

