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
      delay(10);
    }
    //Serial.println("data from ARDUINO: " + data_from_switch);
    //
    //    Serial.println(data_from_switch.charAt(0));

    int index = data_from_switch.indexOf("SSID:");
    if (index > -1)
    {
      String ID = "";
      int k = 0;
      for (int i = index + 5, j = 0; i < data_from_switch.indexOf("::password::"); i++, j++)
      {
        //ID += data_from_switch.charAt(i);
        ssid_1[j] = data_from_switch.charAt(i);
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
      for (int i = data_from_switch.indexOf("::password::") + 12, j = 0; i < data_from_switch.indexOf(":::END::"); i++, j++)
      {
        pass += data_from_switch.charAt(i);
        EEPROM.write(51 + j, pass.charAt(j)); // saving the password
        delay(10);
        EEPROM.commit();
        len++;
        Serial.println(char(EEPROM.read(51 + j)));
      }
      for (int i = 0; i < len; i++)
      {
        password_1[i] = pass.charAt(i);
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

    else if (data_from_switch.charAt(0) >= '0' && data_from_switch.charAt(0) <= '9')
    {

      //      Serial.print("data_from_switch is: ");
      //      Serial.print(data_from_switch);
      //      Serial.println();

      data_for_HUB += "hub:";
      data_for_HUB += Node_Name;
      data_for_HUB += ",";
      data_for_HUB += data_from_switch;

      // Serial.println("data_for_HUB is: " + data_for_HUB);
      //      Serial.println();

      //IPAddress hub_ip_fn(192, 168, 1, 255);
      IPAddress Node_IP = WiFi.localIP();

      Serial.print("AP subnet mask: ");
      subnet = WiFi.subnetMask();
      Serial.println(subnet);

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

      Serial.print("Combined IP= ");
      Serial.println(IP_hub);

      for (int i = 0; i < 5; i++) ///////////////to check for acknowledgement and resend the data in case of no ack
      {
        ///////Send data to HUB/
        UDP.beginPacket(IP_hub, 80);
        char data_for_HUB_local [25];
        convert_to_char(data_for_HUB, data_for_HUB_local);

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

          if (Check_Name.substring(0, 14) == "jackhammer,ack")
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
