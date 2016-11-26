#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
const char* ssid = "Circular Blue";
const char* password = "mightycartoon";
boolean wifiConnected = false;

IPAddress ip(192, 168, 1, 200); //Node static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char ReplyBuffer[] = "acknowledged"; // a string to send back
char ReplyBuffer[] = " mil gaya"; // a string to send back

String Check_Name = "";
String Parse_State = "";

String Node_IP = "";
String Temp_1 = "";
String Temp_2 = "";
String Temp_3 = "";
String Temp_4 = "";

String Octet_1 = "";
String Octet_2 = "";
String Octet_3 = "";
String Octet_4 = "";

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
  //  else
  //  while (1);
}

void loop() {
  Check_Name = "";
  // check if the WiFi and UDP connections were successful
  if (wifiConnected) {
    if (udpConnected) {

      // if there’s data available, read a packet
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
        Serial.print(":");
        Serial.println(UDP.remotePort());

        // read the packet into packetBufffer        
        UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        Serial.println("Contents:");
        
        int value = packetBuffer[0] * 256 + packetBuffer[1];
        for (int i = 0; i < packetSize; i++)
        {
          Serial.print(char(packetBuffer[i]));
          Check_Name += packetBuffer[i];
        }
        Serial.println();
        //Serial.println(value);
        
        // send a reply, to the IP address and port that sent us the packet we received
        Check_Input_String(Check_Name);

        // turn LED on or off depending on value recieved
        digitalWrite(5, value);
      }
      else
        //Serial.println("NO data");
        delay(10);

    }
  }
}


