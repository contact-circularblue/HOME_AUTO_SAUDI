#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>

// wifi connection variables
//char* ssid = "Circular Blue";
//char* password = "mightycartoon";

char ssid_1[25] = "";
char password_1[25] = "";
int ssid_length=0;
int password_length=0;

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
  EEPROM.begin(512);

  ESP.eraseConfig();

  if(EEPROM.read(200)==1)
  {

    Serial.println("flag=1");
    while (!connectWifi())
        delay(100);

      wifiConnected = 1;
      //wifiConnected = 0;

      // only proceed if wifi connection successful

      udpConnected = connectUDP();

      if (udpConnected)
      {
        // initialise pins
        Serial.println("UDP connected");
        //Serial.end();
      }

      Serial.println("done");

  }

  //  // Initialise wifi connection
  //  while (!connectWifi())
  //    delay(100);
  //
  //  // wifiConnected = 1;
  //  wifiConnected = 0;
  //
  //
  //  // only proceed if wifi connection successful
  //
  //
  //  udpConnected = connectUDP();
  //
  //  if (udpConnected) {
  //    // initialise pins
  //    Serial.println("UDP connected");
  //    //Serial.end();
  //  }

  

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
          {
            data_in += char(packetBuffer[i]);
          }
          if (data_in.indexOf("hub:") != -1)
          {
            String data_out = data_in.substring(data_in.indexOf(":") + 1);
            Serial.print(data_out);

            UDP_ACK_Switch();
          }
          //Serial.println("Reached till here");
        }


        if (Serial.available())
        {
          String to_nodes = "";
          while (Serial.available())
          {
            to_nodes += char(Serial.read());

            //            Serial.print("to_nodes= ");
            //            Serial.println(to_nodes);

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
              //Serial.println("ACK RECVD");

              break;
            }


            delay(50);
          }
        }
      }
    }

    else
    {
      ////////////////////////////////////////////////////////////////////////////

      Serial.println("beginning");

      String WiFi_info = "";
      while (!Serial.available())
      {
      }

      while (Serial.available())
      {
        WiFi_info += char(Serial.read());
        delay(10);
      }
      delay(10);

      Serial.print("WiFi_info= ");
      Serial.println(WiFi_info);

      //      while(1)
      //      {
      //        delay(20);
      //      }

      //   int flag=0;
      int index = WiFi_info.indexOf("details:");
      if (index > -1)
      {     
        String ID = "";
        int k = 1;
        for (int i = index + 8, j = 0; i < WiFi_info.indexOf(":pass:"); i++, j++)
        {
          //ID += WiFi_info.charAt(i);
          ssid_1[j] = WiFi_info.charAt(i);
          EEPROM.write(j + 1, ssid_1[j]); // saving the ssid
          delay(100);
          EEPROM.commit();
          k++;
          Serial.println(char(EEPROM.read(j + 1)));
        }
        EEPROM.write(0, k - 1); // saving the length of ssid
        ssid_length=EEPROM.read(0);  // saving the length of ssid
        delay(100);
        EEPROM.commit();


        String pass = "";
        int l = 0;
        for (int i = WiFi_info.indexOf(":pass:") + 6, j = 0; i < WiFi_info.length(); i++, j++)
        {
          //  pass += WiFi_info.charAt(i);
          password_1[j] = WiFi_info.charAt(i);
          EEPROM.write(51 + j, password_1[j]); // saving the password
          delay(100);
          EEPROM.commit();
          l++;
          Serial.println(char(EEPROM.read(51 + j)));
        }
        EEPROM.write(50, l); // saving the length of password
        password_length=l;      // saving the length of password
        delay(100);
        EEPROM.commit();


        Serial.println("SSID length");
        Serial.println(EEPROM.read(0));
       
        Serial.println("password length");
        Serial.println(EEPROM.read(50));

        EEPROM.write(200, 1);  //flag
       
        // Save this ID and password to EEPROM
        /*
          location 0=ID length;  from location 1=ID;  location 50=pass length;   from location 51=pass
        */
        //            EEPROM.write(0, ID.length());
        //            EEPROM.write(50, pass.length());

        //            for (int i = 1; i < ID.length() + 1; i++)
        //            {
        //              EEPROM.write(i, ID.charAt(i - 1));
        //            }
        //
        //            for (int i = 51; i < pass.length() + 51; i++)
        //            {
        //              EEPROM.write(i, ID.charAt(i - 51));
        //            }


        // Send WiFi details to the local network ESP

      }


      while (!connectWifi())
        delay(100);

      wifiConnected = 1;
      //wifiConnected = 0;

      // only proceed if wifi connection successful

      udpConnected = connectUDP();

      if (udpConnected)
      {
        // initialise pins
        Serial.println("UDP connected");
        //Serial.end();
      }

      Serial.println("ending");

      //////////////////////////////////////////////////////////////////////////////////////////////////
    }


  }
}



