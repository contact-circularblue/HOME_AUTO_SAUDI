#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
const char* ssid = "Circular Blue";
const char* password = "mightycartoon";

boolean wifiConnected = false;

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged"; // a string to send back
//char ReplyBuffer[] = " I am 12"; // a string to send back

String Check_Name = "";
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
  //    while (1);
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
        Serial.print("Check_Name:");
        Serial.println(Check_Name);   // Check_Name contains the contents of the packet

        if (Check_Name.substring(0, 10) == "jackhammer")
        {
          //Serial.println("I got it");
          Serial.println(Check_Name.substring(11, 14));
          Serial.print("the node IP is: ");
          //UDP.remoteIP()="192.168.1.200";

          IPAddress Node_IP = WiFi.localIP();
          Serial.println("Node_IP is: ");
          Serial.println(Node_IP);

          /*
             ///////////////////////////////////////////add this fucntion at the end of IPAddress.cpp
            void IPAddress::getIP(String &ip_out){

            String s="";
            for (int i =0; i < 3; i++)
            {
            s+= String(_address.bytes[i], DEC);
            s+='.';
            }
            s+=String(_address.bytes[3], DEC);
            ip_out = s;
            }

            Add this prototype to IPAdderss.h
            void getIP(String &ip_out);
          */


          String ip = Node_IP.getIP();
          Serial.print("ip = ");
          Serial.println(ip);

          Octet_1= ip.substring(0,ip.indexOf("."));
          Serial.print("Octet_1 is:");
          Serial.println(Octet_1);
          int x =Octet_1.length();
          Serial.println(x); 
          
          Temp_2= ip.substring(ip.indexOf(".")+1);
          Octet_2= Temp_2.substring(0,ip.indexOf("."));
          Serial.print("Temp_2 is:");
          Serial.println(Temp_2);
          Serial.print("Octet_2 is:");
          Serial.println(Octet_2);
          int y =Octet_2.length();         
          Serial.println(y);

          Temp_3= Temp_2.substring(Temp_2.indexOf(".")+1);
          Octet_3= Temp_3.substring(0,Temp_3.indexOf("."));
          Serial.print("Temp_3 is:");
          Serial.println(Temp_3);
          Serial.print("Octet_3 is:");
          Serial.println(Octet_3);
          int z =Octet_3.length();         
          Serial.println(z);

          Octet_4= Temp_3.substring(Temp_3.indexOf(".")+1);
          Serial.print("Octet_4 is:");
          Serial.println(Octet_4);
          int v =Octet_4.length();         
          Serial.println(v);
          
          UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
          UDP.write(ReplyBuffer);
          UDP.endPacket();
        }
        // turn LED on or off depending on value recieved
        digitalWrite(5, value);
      }
      else
        Serial.println("NO data");
      delay(10);

    }

  }

}

// connect to UDP – returns true if successful or false if not
boolean connectUDP() {
  boolean state = false;

  Serial.println("");
  Serial.println("Connecting to UDP");

  if (UDP.begin(localPort) == 1) {
    Serial.println("Connection successful");
    state = true;
  }
  else {
    Serial.println("Connection failed");
  }

  return state;
}
// connect to wifi – returns true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 30) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  return state;
}
