bool UDP_ACK()
{
  //Serial.println("ACK CHECK------------------");
   int packetSize = 0;
   packetSize = UDP.parsePacket();
  if (packetSize)
  {
    IPAddress remote = UDP.remoteIP();
    
    // read the packet into packetBufffer
    UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    //Serial.println("Contents:");
    //int value = packetBuffer[0]*256 + packetBuffer[1];
    //    for (int i = 0; i < packetSize; i++)
    //      Serial.print(char(packetBuffer[i]));
    //    Serial.println();

//    if (packetBuffer[0] = 'a')
//    {
//      if (packetBuffer[1] = 'c')
//      {
//        if (packetBuffer[0] = 'k')
//        {
//          //Serial.println("GOT ACK!!!!!!!!!!!!!!!");
//          return true;
//        }
//      }
//    }

//    else
//      return false;
//    //          Serial.println(packetBuffer);
//    //          Serial.println(packetSize);
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
      //      break;
          }

  }
}

