#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <EEPROM.h>

// wifi connection variables
char ssid_1[25] = "";
char password_1[25] = "";
int ssid_length = 0;
int password_length = 0;

//const char* ssid = "Circular Blue";
//const char* password = "mightycartoon";
boolean wifiConnected = false;

//IPAddress ip(192, 168, 1, 200); //Node static IP
//IPAddress gateway(192, 168, 1, 1);
//IPAddress subnet(255, 255, 255, 0);
//
//IPAddress IP_hub(192, 168, 1, 200);

// UDP variables
unsigned int localPort = 80;
WiFiUDP UDP;
boolean udpConnected = false;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char ReplyBuffer[] = "acknowledged"; // a string to send back
char ReplyBuffer[] = "hub:jackhammer,ack"; // a string to send back

String Node_Name = "jackhammer";
String Check_Name = "";
String Parse_State = "";
String data_from_switch = "";
String data_for_HUB = "";

String Node_IP = "";
String senders_ip = "";
String Temp_1 = "";
String Temp_2 = "";
String Temp_3 = "";
String Temp_4 = "";

String Octet_1 = "";
String Octet_2 = "";
String Octet_3 = "";
String Octet_4 = "";

void setup()
{
  // Initialise Serial connection
  //Serial.begin(115200);
  Serial.begin(9600);
  EEPROM.begin(512);

  Serial.print("Started");

  WiFi.disconnect();

  EEPROM.write(200, 1); // Remove this in final product
  delay(100);
  EEPROM.commit();



  //  while(1)
  //  {
  //    if(Serial.available())
  //    Serial.print(char(Serial.read()));
  //    delay(10);
  //  }

//  while (Serial.available())
//  {
//    Serial.read();
//  }

  // Initialise wifi connection
 // connectWifi();

  // only proceed if wifi connection successful
  //  if (wifiConnected) {
  //    udpConnected = connectUDP();
  //    if (udpConnected) {
  //      // initialise pins
  //      Serial.println("UDP connected");
  //    }
  //  }
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

    if (Serial.available())
    {

      String WiFi_info = "";
      while (!Serial.available())
      {
        delay(1);
      }

      while (Serial.available())
      {
        WiFi_info += char(Serial.read());
        delay(10);
      }
      delay(10);


      Serial.print("WiFi_info= ");
      Serial.println(WiFi_info);

      int index = WiFi_info.indexOf("SSID:");
      if (index > -1)
      {
        String test_SSID=WiFi_info.substring(WiFi_info.indexOf("SSID:")+5,WiFi_info.indexOf("::PASSWORD::"));
        String test_pass=WiFi_info.substring(WiFi_info.indexOf("::password::")+12,WiFi_info.indexOf(":::END:::"));

        Serial.println("test_SSID= "+test_SSID);
        Serial.println("test_pass= "+test_pass);
        
        String ID = "";
        int k = 0;
        for (int i = index + 5, j = 0; i < WiFi_info.indexOf("::password::"); i++, j++)
        {
          //ID += WiFi_info.charAt(i);
          ssid_1[j] = WiFi_info.charAt(i);
          EEPROM.write(j + 1, ssid_1[j]); // saving the ssid
          delay(10);
          EEPROM.commit();
          k++;
          Serial.println(char(EEPROM.read(j + 1)));
        }
        EEPROM.write(0, k); // saving the length of ssid
        ssid_length = EEPROM.read(0); // saving the length of ssid
        delay(10);
        EEPROM.commit();

        Serial.print("SSID in EEPROM");

        String pass = "";
        int len = 0;
        for (int i = WiFi_info.indexOf("::password::") + 12, j = 0; i < WiFi_info.indexOf(":::END:::"); i++, j++)
        {
          password_1[j] = WiFi_info.charAt(i);
          EEPROM.write(51 + j, password_1[j]); // saving the password
          delay(10);
          EEPROM.commit();
          len++;
          Serial.println(char(EEPROM.read(51 + j)));
        }
        EEPROM.write(50, len); // saving the length of password
        password_length = len;    // saving the length of password
        delay(10);
        EEPROM.commit();

        Serial.print("PASSWORD in EEPROM");

        Serial.println("SSID length");
        Serial.println(EEPROM.read(0));

        Serial.println("password length");
        Serial.println(EEPROM.read(50));

        EEPROM.write(200, 1);
        delay(100);
        EEPROM.commit();
        Serial.println("EEPROM Edited");
      }
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
          Serial.print("RECEIVED FROM HUB="+Check_Name);


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
  }
  else if (EEPROM.read(200) == 0)
  {
    Serial.print("Flag Found 0");
    //   wifiConnected = connectWifi();
    //   if (wifiConnected==false)
    {
      String WiFi_info = "";
      while (!Serial.available())
      {
        delay(1);
      }

      while (Serial.available())
      {
        WiFi_info += char(Serial.read());
        delay(10);
      }
      delay(10);

      Serial.print("WiFi_info= ");
      Serial.println(WiFi_info);

      int index = WiFi_info.indexOf("SSID:");
      if (index > -1)
      {

        String test_SSID=WiFi_info.substring(WiFi_info.indexOf("SSID:")+5,WiFi_info.indexOf("::PASSWORD::"));
        String test_pass=WiFi_info.substring(WiFi_info.indexOf("::password::")+12,WiFi_info.indexOf(":::END:::"));

        Serial.println("test_SSID= "+test_SSID);
        Serial.println("test_pass= "+test_pass);
        
        String ID = "";
        int k = 0;
        int j = 0;
        for (int i = index + 5; i < WiFi_info.indexOf("::password::"); i++)
        {
          //ID += WiFi_info.charAt(i);
          ssid_1[j] = WiFi_info.charAt(i);
          EEPROM.write(j + 1, ssid_1[j]); // saving the ssid
          delay(10);
          EEPROM.commit();
          k++;
          Serial.print(char(EEPROM.read(j + 1)));
          j++;
        }
        EEPROM.write(0, k); // saving the length of ssid
        ssid_length = EEPROM.read(0); // saving the length of ssid
        delay(10);
        EEPROM.commit();

        Serial.print("SSID in EEPROM");

        String pass = "";
        int len = 0;
        for (int i = WiFi_info.indexOf("::password::") + 12, j = 0; i < WiFi_info.indexOf(":::END::"); i++, j++)
        {
          password_1[j] = WiFi_info.charAt(i);
          EEPROM.write(51 + j, password_1[j]); // saving the password
          delay(10);
          EEPROM.commit();
          len++;
          Serial.println(char(EEPROM.read(51 + j)));
        }
        EEPROM.write(50, len); // saving the length of password
        password_length = len;    // saving the length of password
        delay(10);
        EEPROM.commit();

        Serial.print("PASSWORD in EEPROM");

        Serial.println("SSID length");
        Serial.println(EEPROM.read(0));

        Serial.println("password length");
        Serial.println(EEPROM.read(50));

        EEPROM.write(200, 1);
        delay(10);
        EEPROM.commit();
        Serial.println("EEPROM Edited");

        //        connectWifi();
      }
    }
  }
}


