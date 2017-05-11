#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>

// wifi connection variables
//char* ssid_T = "Circular Blue";
//char* password_T = "mightycartoon";
char buf[100];


char ssid_1[25] = "";
char password_1[25] = "";
int ssid_length = 0;
int password_length = 0;

boolean wifiConnected = false;
int counter = 1;

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char ReplyBuffer[] = "jackhammer,ack"; // a string to send back
//char ReplyBuffer[] = "mil gaya"; // a string to send back

IPAddress IP_hub;
IPAddress subnet;

byte octate1, octate2, octate3, octate4;

void setup() {
  // Initialise Serial connection
  Serial.begin(9600);
  EEPROM.begin(512);

//  Serial.println("ESP_UDP_START");
  //  EEPROM.write(200, 0);
  //  delay(100);
  //  EEPROM.commit();
  Serial.print("EEPROM =");
  Serial.println(EEPROM.read(200));

  //  Serial.println("here");
  //  //  EEPROM.write(200, 1);
  //  //  delay(100);
  //  //  EEPROM.commit();
  //
  //
  //  Serial.print("EEPROM.read(200)=");
  //  Serial.println(EEPROM.read(200));

  if (EEPROM.read(200) == 1)
  {

//    Serial.println("flag=1");
    while (!connectWifi())
      delay(100);

    wifiConnected = 1;
    //wifiConnected = 0;

    // only proceed if wifi connection successful

    udpConnected = connectUDP();

    if (udpConnected)
    {
      // initialise pins
//      Serial.println("UDP connected");
      //Serial.end();
    }

    Serial.println("done");

  }
}

void loop()
{
  delay(1);
  if (WiFi.status() != WL_CONNECTED && EEPROM.read(200) == 1)
  {
    while (!connectWifi())
      delay(100);

    if (EEPROM.read(200) == 0)
      EEPROM.write(200, 1);
    delay(100);
    EEPROM.commit();

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

    //      Serial.println("ending");
  }

  if (wifiConnected) {
    if (udpConnected) {
      delay(1);
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
        {
          data_in += char(packetBuffer[i]);
        }
        //        if (data_in.indexOf("hub:") != -1)
        //        {
        //          String data_out = data_in.substring(data_in.indexOf(":") + 1);
        //          Serial.print(data_out);
        //
        //          UDP_ACK_Switch();
        //        }
        //        Serial.println("data_in_from_node:");
        //        Serial.println(data_in);

        StaticJsonBuffer<300> Buffer;
        JsonObject& from_node = Buffer.parseObject(data_in);
        String success = from_node[String("s")];

        if (!from_node.success())
        {
          Serial.println("incoming parseObject() failed");
          //          return;
        }

        else if (success == "t")
        {
          String nId = from_node[String("nId")];
          String dId = from_node[String("dId")];
          String ACK = from_node[String("ACK")];
          String REQ = from_node[String("REQ")];
          String VAL = from_node[String("VAL")];

          UDP_ACK_Switch(nId);

          if (ACK == "F")
            Serial.print(data_in);
        }
        //Serial.println("Reached till here");
      }


      if (Serial.available())
      {
        String to_nodes = "";
        while (Serial.available())
        {
          to_nodes += char(Serial.read());
          delay(10);
        }

        StaticJsonBuffer<300> Buffer_out;

        JsonObject& from_hub = Buffer_out.parseObject(to_nodes);

        Serial.print("to_nodes= ");
        Serial.println(to_nodes);

        //        Serial.print("S=");
        //        String success=from_hub[String("s")];
        //        Serial.println(success);

        if (!from_hub.success())
        {
          //          Serial.println("parseObject() failed");

          if (to_nodes.indexOf("RESET_ESP") != -1)
          {
            EEPROM.write(200, 0);
            delay(100);
            EEPROM.commit();
            delay(100);
            Serial.println("RESETTING");
            ESP.reset();
          }
        }

        else
        {
          String success = from_hub[String("s")];
          if (success == "t")
          {
            // Serial.println("s:t found");
            char char_to_nodes[25];

            for (int i = 0; i < 5; i++)
            {

              //UDP.beginPacket("192.168.1.255", 80);

              IPAddress Node_IP = WiFi.localIP();

              // Serial.println("LOCAL IP");

              //            Serial.print("AP subnet mask: ");
              subnet = WiFi.subnetMask();
              //            Serial.println(subnet);

              seperate_octets(Node_IP);
              byte IP_octate1 = octate1;
              byte IP_octate2 = octate2;
              byte IP_octate3 = octate3;
              byte IP_octate4 = octate4;

              seperate_octets(subnet);//, octate1, octate2, octate3, octate4);

              //IPAddress IP_hub_temp(octate1, octate2, octate3, 200);
              // Serial.println("SEPERATING OCTETS");

              byte octate1_2, octate2_2, octate3_2, octate4_2;

              if (octate1 < 255)
              {
                octate1 = 255 - octate1;
              }
              else
              {
                octate1 = IP_octate1;
              }
              if (octate2 < 255)
              {
                octate2 = 255 - octate2;
              }
              else
              {
                octate2 = IP_octate2;
              }
              if (octate3 < 255)
              {
                octate3 = 255 - octate3;
              }
              else
              {
                octate3 = IP_octate3;
              }
              if (octate4 < 255)
              {
                octate4 = 255 - octate4;
              }
              else
              {
                octate4 = IP_octate4;
              }

              // Serial.println("FORMING BROADCAST IP");

              IPAddress IP_hub_temp(octate1, octate2, octate3, octate4);

              IP_hub = IP_hub_temp;

              //  Serial.print("Combined IP= ");
              //  Serial.println(IP_hub);

              //Serial.println("to_nodes="+to_nodes);

              // convert_to_char(to_nodes, char_to_nodes);
              //            Serial.print("Sending:");
              //            Serial.println(char_to_nodes);
              char to_nodes_chars[100];
              stringToCharArray(to_nodes, to_nodes_chars);

              // Serial.println("SENDING UDP");

              UDP.beginPacket(IP_hub, 80);

              UDP.write(to_nodes_chars);
              // Serial.println("SENT:");
              // Serial.println(to_nodes_chars);


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
    }
  }

  else
  {
    ////////////////////////////////////////////////////////////////////////////

    //      Serial.println("beginning");

    String WiFi_info = "";
    while (!Serial.available())
    {
    }

    while (Serial.available())
    {
      WiFi_info += char(Serial.read());
      delay(3);
    }
    delay(10);

//    Serial.print("WiFi_info= ");
//    Serial.println(WiFi_info);

    int index = WiFi_info.indexOf("details::pass:");
    Serial.print("index=");
    Serial.println(index);
    if (index > -1)
    {
//      Serial.println("found details::pass:");

      String GOT_SSID = WiFi_info.substring(WiFi_info.indexOf("details::pass:") + 14, WiFi_info.indexOf("hub_pass:"));
      String GOT_pass = WiFi_info.substring(WiFi_info.indexOf("hub_pass:") + 9);

//      Serial.print("GOT SSID:");
//      Serial.println(GOT_SSID);
//      Serial.print("GOT_pass:");
//      Serial.println(GOT_pass);

      for (int i = 0; i < GOT_SSID.length(); i++)
      {
        ssid_1[i] = GOT_SSID.charAt(i);
        EEPROM.write(i + 1, ssid_1[i]); // saving the ssid
        delay(5);
        EEPROM.commit();
//        Serial.print(char(EEPROM.read(i + 1)));
      }

      EEPROM.write(0, GOT_SSID.length()); // saving the length of ssid
      ssid_length = EEPROM.read(0); // saving the length of ssid
      EEPROM.commit();


      for (int i = 0; i < GOT_pass.length(); i++)
      {
        password_1[i] = GOT_pass.charAt(i);
        EEPROM.write(i + 51, password_1[i]); // saving the ssid
        delay(5);
        EEPROM.commit();
//        Serial.print(char(EEPROM.read(i + 1)));
      }

      EEPROM.write(50, GOT_pass.length()); // saving the length of ssid
      password_length = EEPROM.read(50); // saving the length of ssid
      EEPROM.commit();
      
      Serial.print("WIFI_ACK");

      //        Serial.print("SSID in EEPROM");

      //      while (1)
      //        delay(1);

      //      String pass = "";
      //      int l = 0;
      //      for (int i = WiFi_info.indexOf("hub_pass:") + 9, j = 0; i < WiFi_info.length(); i++, j++)
      //      {
      //        pass += WiFi_info.charAt(i);
      //        password_1[j] = WiFi_info.charAt(i);
      //        EEPROM.write(51 + j, password_1[j]); // saving the password
      //        delay(100);
      //        EEPROM.commit();
      //        l++;
      //        Serial.print(char(EEPROM.read(51 + j)));
      //      }
      //      Serial.println();
      //
      //
      //      EEPROM.write(50, l); // saving the length of password
      //      password_length = l;    // saving the length of password
      //      delay(100);
      //      EEPROM.commit();


      while (!connectWifi())
        delay(100);

      if (EEPROM.read(200) == 0)
      {
        EEPROM.write(200, 1);
        delay(100);
        EEPROM.commit();
        
        
//        delay(1000);
      }

      ESP.reset();



      //wifiConnected = 0;

      // only proceed if wifi connection successful
      if (WiFi.status() == WL_CONNECTED)
      {
        udpConnected = connectUDP();

        if (udpConnected)
        {
          // initialise pins
//          Serial.println("UDP connected");
          //Serial.end();
        }
      }
      //        Serial.print("PASSWORD in EEPROM");


      //        Serial.println("SSID length");
      //        Serial.println(EEPROM.read(0));
      //
      //        Serial.println("password length");
      //        Serial.println(EEPROM.read(50));


      //        Serial.println("EEPROM Edited");



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

    if (EEPROM.read(200) == 1 && WiFi.status() != WL_CONNECTED)
    {
      while (!connectWifi())
        delay(100);

      if (EEPROM.read(200) == 0)
        EEPROM.write(200, 1);
      delay(100);
      EEPROM.commit();

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

      //      Serial.println("ending");
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
  }
}



char* stringToCharArray(String str, char *buffer)
{
  str.toCharArray(buffer, 100);
  return buffer;
}
