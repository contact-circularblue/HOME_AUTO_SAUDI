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
    //    Serial.println("data from ARDUINO: " + data_from_switch);
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

      Serial.print("data_for_HUB is: " + data_for_HUB);
      Serial.println();

      IPAddress hub_ip_fn(192, 168, 1, 255);


      ////////Send data to HUB
      UDP.beginPacket(hub_ip_fn, 80);
      char data_for_HUB_local [25];

      convert_to_char(data_for_HUB, data_for_HUB_local);

      UDP.write(data_for_HUB_local);
      UDP.endPacket();


      while (1)                                          // waiting for acknowledgement for the packet send to the hub
      {
        int packetSize = UDP.parsePacket();
        if (packetSize)
        {
          //        Serial.println("");
          //        Serial.print("Received packet of size ");
          //        Serial.println(packetSize);
          //        Serial.print("From ");
         // IPAddress remote = UDP.remoteIP();
          for (int i = 0; i < 4; i++)
          {
            //          Serial.print(remote[i], DEC);
            if (i < 3)
            {
              //            Serial.print(".");
            }
          }
          //        Serial.print(", port ");
          //        Serial.print(":");
          //        Serial.println(UDP.remotePort());

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
          //Serial.print("RECEIVED FROM HUB="+Check_Name);


          // send a reply, to the IP address and port that sent us the packet we received
          if (Check_Name.substring(0, 14) == "jackhammer,ack")
            Serial.print("I got acknowledgement");
          Check_Name = "";
          
        }

        //Serial.println("NO data");
        delay(10);
        break;
      }

      data_from_switch = "";
      data_for_HUB = "";

    }

  }
}






