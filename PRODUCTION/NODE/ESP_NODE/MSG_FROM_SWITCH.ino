#include <Arduino.h>

void Msg_from_switch()
{
  if (Serial.available())
  {
    //Serial.println("Serial Is Available");
    data_from_switch = "";
    data_for_HUB = "";
    //    Serial.println("Initially:");
    //    Serial.print("data from ARDUINO: " + data_from_switch);
    //    Serial.println();

    while (Serial.available())
    {
      data_from_switch += char(Serial.read());
      // Serial.println(data_from_switch);
      delay(20);
    }
//    Serial.println("data from ARDUINO: " + data_from_switch);
    //
    //    Serial.println(data_from_switch.charAt(0));

    int index = data_from_switch.indexOf("SSID:::password");
    if (index > -1)
    {

      String test_SSID = data_from_switch.substring(data_from_switch.indexOf("SSID:::password::") + 17, data_from_switch.indexOf("hub_pass"));
      String test_pass = data_from_switch.substring(data_from_switch.indexOf("hub_pass") + 9, data_from_switch.indexOf(":::END::"));

      Serial.println("test_SSID= " + test_SSID);
      Serial.println("test_pass= " + test_pass);

      String ID = "";
      int k = 0;
      int j = 0;
      for (int i = 0; i < test_SSID.length(); i++)
      {
        //ID += data_from_switch.charAt(i);
        ssid_1[i] = test_SSID.charAt(i);
        EEPROM.write(i + 1, ssid_1[i]); // saving the ssid
        delay(3);
        EEPROM.commit();
        k++;
        Serial.print(char(EEPROM.read(j + 1)));
      }
      Serial.println();
      EEPROM.write(0, k); // saving the length of ssid
      ssid_length = EEPROM.read(0); // saving the length of ssid
      delay(3);
      EEPROM.commit();

      Serial.print("SSID in EEPROM");

      k = 0;
      String pass = "";
      for (int i = 0; i < test_pass.length(); i++)
      {
        //ID += data_from_switch.charAt(i);
        password_1[i] = test_pass.charAt(i);
        EEPROM.write(i + 51, password_1[i]); // saving the ssid
        delay(3);
        EEPROM.commit();
        k++;
        Serial.print(char(EEPROM.read(j + 1)));
      }
      Serial.println();
      EEPROM.write(50, k); // saving the length of password
      delay(3);
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

      connectWifi();
    }

    else if (data_from_switch.charAt(0) >= '0' && data_from_switch.charAt(0) <= '9')
    {

            Serial.print("data_from_switch is: ");
            Serial.print(data_from_switch);
            Serial.println();

      StaticJsonBuffer<300> Buffer_node_msg;

      JsonObject& node_msg = Buffer_node_msg.createObject();

      node_msg["nId"] = Node_Name;
      node_msg["s"] = String("t");
      node_msg["ACK"] = "F";
      node_msg["REQ"] = String(data_from_switch.charAt(0));

      String t0 = data_from_switch.substring(data_from_switch.indexOf(",") + 1 );
      //      Serial.print("t0=");
      //      Serial.println(t0);

      String dId = t0.substring(0, t0.indexOf(","));
                  Serial.print("dId=");
                  Serial.println(dId);

      String VAL = t0.substring(t0.indexOf(",") + 1);
                  Serial.print("VAL=");
                  Serial.println(VAL);




      node_msg["dId"] = dId;
      node_msg["VAL"] = VAL;

      String json_node_msg = "";
      node_msg.printTo(json_node_msg);

            Serial.print("json_node_msg:");
            Serial.println(json_node_msg);

      //      data_for_HUB += "hub:";
      //      data_for_HUB += Node_Name;
      //      data_for_HUB += ",";
      //      data_for_HUB += data_from_switch;

      // Serial.println("data_for_HUB is: " + data_for_HUB);
      //      Serial.println();

      //IPAddress hub_ip_fn(192, 168, 1, 255);
      IPAddress Node_IP = WiFi.localIP();

      //      Serial.print("AP subnet mask: ");
      subnet = WiFi.subnetMask();
      //      Serial.println(subnet);

      seperate_octets(Node_IP);
      byte IP_octate1 = octate1;
      byte IP_octate2 = octate2;
      byte IP_octate3 = octate3;
      byte IP_octate4 = octate4;

      seperate_octets(subnet);//, octate1, octate2, octate3, octate4);

      //IPAddress IP_hub_temp(octate1, octate2, octate3, 200);

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

      IPAddress IP_hub_temp(octate1, octate2, octate3, octate4);

      IP_hub = IP_hub_temp;

      //      Serial.print("Combined IP= ");
      //      Serial.println(IP_hub);

      for (int i = 0; i < 5; i++) ///////////////to check for acknowledgement and resend the data in case of no ack
      {
        ///////Send data to HUB/
        UDP.beginPacket(IP_hub, 80);
        char data_for_HUB_local [100];
        convert_to_char(json_node_msg, data_for_HUB_local);

        //        Serial.print("data_for_HUB_local=");
        //        Serial.println(data_for_HUB_local);

        UDP.write(data_for_HUB_local);
        UDP.endPacket();

        delay(500);

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
            Check_Name += packetBuffer[i];
          }
          //          Serial.println();
          //          Serial.println("RECEIVED FROM HUB=" + Check_Name);

          if (Check_Name.substring(0, 14) == (Node_Name + ",ack"))
          {
            //            Serial.println("Contents:");
            //for (int i = 0; i < packetSize; i++)
            //              Serial.print(char(packetBuffer[i]));

            //Serial.print("recv ack");
            Check_Name = "";
            break;
          }
        }

        delay(50);
      }

      data_from_switch = "";
      data_for_HUB = "";
    }
  }
}
