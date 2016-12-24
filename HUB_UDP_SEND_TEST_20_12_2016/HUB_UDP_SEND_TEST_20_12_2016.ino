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
String Check_Message = "";

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


 //       if (Serial.available())
        {
          String to_nodes = "";
//          while (Serial.available())
//          {
//            to_nodes += char(Serial.read());
//            delay(10);
//          }


          to_nodes = "jackhammer,0,1,1";
          
          char char_to_nodes[25];

          while (1)   ///////////////to check for acknowledgement from node and in resend data in case of no ack
          {
            ///////Send data to NODE
            UDP.beginPacket("192.168.1.255", 80);
            convert_to_char(to_nodes, char_to_nodes);
            //Serial.print("Sending:");
            //Serial.println(char_to_nodes);
            UDP.write(char_to_nodes);
            UDP.endPacket();

            delay(50);

            //            unsigned long previousMillis = 0;        // will store last time LED was updated
            //            // constants won't change :
            //            const long interval = 5000;
            //            int count_no_ack = 0;
            //          while (1)
            //          {
            //            unsigned long currentMillis = millis();
            //            if (currentMillis - previousMillis >= interval)
            //            {
            //              previousMillis = currentMillis;
            //              //Serial.println("ACK not found");
            //              count_no_ack++;
            //              if (count_no_ack == 2)
            //                break;
            //            }
            //            else
            //            {
            //              //Serial.println("else case");
            //
            //             // if (UDP_ACK())
            //              {
            //                //Serial.println("ACK RECVD");
            //
            //                break;
            //              }
            //
            //            }
            //          }

            int packetSize = 0;
            packetSize = UDP.parsePacket();
            if (packetSize)
            {
              IPAddress remote = UDP.remoteIP();

              // read the packet into packetBufffer
              UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

              for (int i = 0; i < packetSize; i++)
              {
                //  Serial.print(char(packetBuffer[i]));
                Check_Message += packetBuffer[i];
              }
              Serial.println();
              Serial.print("RECEIVED FROM HUB=" + Check_Message);

              if (Check_Message.substring(0, 18) == "hub:jackhammer,ack")
              {
                Serial.println("Contents:");
                for (int i = 0; i < packetSize; i++)
                  Serial.print(char(packetBuffer[i]));

                Serial.print("acknowledged from node");
                Check_Message = "";
                break;
              }

            }
          }
          delay(50);

        }
         delay(2000);
        
      }
    }
  }
}



