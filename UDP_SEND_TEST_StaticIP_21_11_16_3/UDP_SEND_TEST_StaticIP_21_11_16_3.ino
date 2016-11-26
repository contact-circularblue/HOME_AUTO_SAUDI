#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
const char* ssid = "Circular Blue";
const char* password = "mightycartoon";
boolean wifiConnected = false;
int counter=1;

IPAddress ip(192, 168, 1, 204); //Node static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged"; // a string to send back
//char ReplyBuffer[] = "mil gaya"; // a string to send back

void setup() {
  // Initialise Serial connection
  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  // only proceed if wifi connection successful
  if (wifiConnected) {
    udpConnected = connectUDP();
    if (udpConnected) {
      // initialise pins
      Serial.println("UDP connected");
    }
  }
}

void loop() {
  // check if the WiFi and UDP connections were successful
  if (wifiConnected) {
    if (udpConnected) {

      // if there’s data available, read a packet

      // send a reply, to the IP address and port that sent us the packet we received
      UDP.beginPacket("192.168.1.200", 80);
      /*     //UDP.write("HI! via UDP");
           Serial.print("jackhammer,1,1");
           UDP.write("jackhammer,1,1");
      */
      Request_Case(counter);
      //UDP.write("jackhammer,1,0");
      counter++;
      if (counter > 8)
      {
        counter = 1;
      }

      UDP.endPacket();

      // turn LED on or off depending on value recieved

    }
    //delay(10);
    delay(2000);

    int packetSize = UDP.parsePacket();
    if (packetSize)
    {
      Serial.println("");
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remote = UDP.remoteIP();
      for (int i = 0; i < 4; i++)
      {
        Serial.print(remote[i], DEC);
        if (i < 3)
        {
          Serial.print(".");
        }
      }
      Serial.print(", port ");
      Serial.println(UDP.remotePort());

      // read the packet into packetBufffer
      UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
      Serial.println("Contents:");
      //int value = packetBuffer[0]*256 + packetBuffer[1];
      for (int i = 0; i < packetSize; i++)
        Serial.print(char(packetBuffer[i]));

    }
  }
}



