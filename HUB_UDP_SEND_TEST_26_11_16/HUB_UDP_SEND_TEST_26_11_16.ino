#include <ESP8266WiFi.h>
#include <WiFiUDP.h>

// wifi connection variables
char* ssid = "Circular Blue";
char* password = "mightycartoon";
boolean wifiConnected = false;
int counter = 1;



// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char ReplyBuffer[] = "jackhammer,ack"; // a string to send back
//char ReplyBuffer[] = "mil gaya"; // a string to send back

void setup() {
  // Initialise Serial connection
  Serial.begin(9600);

  ESP.eraseConfig();

  // Initialise wifi connection
  while (!connectWifi())
    delay(100);

  wifiConnected = 1;

  // only proceed if wifi connection successful


  udpConnected = connectUDP();
  if (udpConnected) {
    // initialise pins
    Serial.println("UDP connected");

    //Serial.end();
  }

}

void loop() {

  //Serial.println("Entering loop");
  // check if the WiFi and UDP connections were successful
  //Serial.begin(9600);
  //while(1)
  {

    if (wifiConnected) {
      if (udpConnected) {
        //Serial.println("WiFi & UDP connected");

        //if (Serial.available())

        int packetSize = UDP.parsePacket();
        if (packetSize)
        {
          //          Serial.println("");
          //          Serial.print("Received packet of size ");
          //          Serial.println(packetSize);
          //          Serial.print("From ");
          //          IPAddress remote = UDP.remoteIP();
          //          for (int i = 0; i < 4; i++)
          //          {
          //            Serial.print(remote[i], DEC);
          //            if (i < 3)
          //            {
          //              Serial.print(".");
          //            }
          //          }
          //          Serial.print(", port ");
          //          Serial.println(UDP.remotePort());

          // read the packet into packetBufffer
          UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
          //Serial.println("Contents:");
          //int value = packetBuffer[0]*256 + packetBuffer[1];
          String data_in = "";
          for (int i = 0; i < packetSize; i++)
            data_in += char(packetBuffer[i]);
          if (data_in.indexOf("hub:") != -1)
          {
            String data_out = data_in.substring(data_in.indexOf(":") + 1);
            Serial.print(data_out);
            Serial.println();

            UDP_ACK_Switch();
          }
          Serial.println("Reached till here");
        }


        if (Serial.available())
        {
          String to_nodes = "";
          while (Serial.available())
          {
            to_nodes += char(Serial.read());
            delay(10);
          }

          char char_to_nodes[25];



          while (1)
          {

            UDP.beginPacket("192.168.1.255", 80);
            convert_to_char(to_nodes, char_to_nodes);
            //            Serial.print("Sending:");
            //            Serial.println(char_to_nodes);
            UDP.write(char_to_nodes);


            UDP.endPacket();




            delay(500);
            if (UDP_ACK())
            {
              Serial.println("ACK RECVD");

              break;
            }


            delay(50);
          }

        }
      }
    }
  }
}



