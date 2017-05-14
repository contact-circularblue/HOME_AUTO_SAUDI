#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>


//CHANGE THESE FOR EACH NODE
String Node_Name = "4WQt8Wn0y8";
char ReplyBuffer[] = "hub:4WQt8Wn0y8,ack";
//----------------------------------------


char buf[100];

// wifi connection variables
char ssid_1[25] = "";
char password_1[25] = "";
int ssid_length = 0;
int password_length = 0;

//const char* ssid = "Circular Blue";
//const char* password = "mightycartoon";
boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char ReplyBuffer[] = "acknowledged"; // a string to send back



String Check_Name = "";
String Parse_State = "";
String data_from_switch = "";
String data_for_HUB = "";



IPAddress IP_hub;
IPAddress subnet;

byte octate1, octate2, octate3, octate4;



void setup()
{
  // Initialise Serial connection
  //Serial.begin(115200);
  Serial.begin(9600);
  EEPROM.begin(512);

  Serial.print("Started");

  WiFi.disconnect();

  delay(1000);
  
  Serial.print("EEPROM at 200=");
  Serial.println(EEPROM.read(200));

//  EEPROM.write(200, 0); // Remove this in final product
//  delay(100);
//  EEPROM.commit();
}

void loop()
{
  if (EEPROM.read(200) == 1)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      wifiConnected = connectWifi();
      udpConnected = connectUDP();
    }



    Check_Name = "";
    // check if the WiFi and UDP connections were successful
    if (wifiConnected) {

      if (udpConnected) {

        // if there’s data available, read a packet
        int packetSize = UDP.parsePacket();
        if (packetSize)
        {
          IPAddress remote = UDP.remoteIP();
          // read the packet into packetBufffer
          UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
          //        Serial.println("Contents:");

          int value = packetBuffer[0] * 256 + packetBuffer[1];
          for (int i = 0; i < packetSize; i++)
          {
            //          Serial.print(char(packetBuffer[i]));
            Check_Name += packetBuffer[i];
          }
          //        Serial.println();
          //          Serial.print("RECEIVED FROM HUB="+Check_Name);


          // send a reply, to the IP address and port that sent us the packet we received
          Check_Input_String(Check_Name);

          //        ACK_THE_HUB();
          //        Serial.println("Ack send by node");
        }

        Msg_from_switch(); // send the change made on the physical switch to hub

        // Serial.println("NO data");
        delay(10);
      }
    }
    else
    {
      get_details();
    }
    delay(1);
  }
  else if (EEPROM.read(200) == 0)
  {
    //    Serial.print("Flag Found 0");
    //   wifiConnected = connectWifi();
    //   if (wifiConnected==false)
    {
      get_details();
    }
    delay(1);
  }
}


char* stringToCharArray(String str, char *buffer)
{
  str.toCharArray(buffer, 100);
  return buffer;
}
