void Msg_from_switch()
{

  if (Serial.available())
  {
    data_from_switch = "";
    data_for_HUB = "";
    //    Serial.println("Initially:");
    //    Serial.print("data from ARDUINO: " + data_from_switch);
    //    Serial.println();


    while (Serial.available())
    {
      data_from_switch += char(Serial.read());
      delay(1);
    }
        Serial.println("data from ARDUINO: " + data_from_switch);
    //
    //    Serial.println(data_from_switch.charAt(0));

    if (data_from_switch.charAt(0) >= '0' && data_from_switch.charAt(0) <= '9')
    {

      //      Serial.print("data_from_switch is: ");
      //      Serial.print(data_from_switch);
      //      Serial.println();

      data_for_HUB += "hub:";
      data_for_HUB += Node_Name;
      data_for_HUB += ",";
      data_for_HUB += data_from_switch;

      //      Serial.println("data_for_HUB is: " + data_for_HUB);
      //      Serial.println();

      IPAddress hub_ip_fn(192, 168, 1, 255);

      while (1)  ///////////////to check for acknowledgement and in resend the data in case of no ack
      {
        ///////Send data to HUB/
        UDP.beginPacket(hub_ip_fn, 80);
        char data_for_HUB_local [25];
        convert_to_char(data_for_HUB, data_for_HUB_local);

        UDP.write(data_for_HUB_local);
        UDP.endPacket();

        delay(50);

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

            Serial.print("recv ack");
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






