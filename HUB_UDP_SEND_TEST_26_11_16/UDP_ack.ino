bool UDP_ACK()
{
  //Serial.println("ACK CHECK------------------");
  int packetSize = UDP.parsePacket();
  if (packetSize)
  {
    //Serial.println("");
    //Serial.print("Received packet of size ");
    //Serial.println(packetSize);
    //Serial.print("From ");
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
    //    for (int i = 0; i < packetSize; i++)
    //      Serial.print(char(packetBuffer[i]));
    //    Serial.println();

    if (packetBuffer[0] = 'a')
    {
      if (packetBuffer[1] = 'c')
      {
        if (packetBuffer[0] = 'k')
        {
          //Serial.println("GOT ACK!!!!!!!!!!!!!!!");
          return true;
        }
      }
    }

    else
      return false;
    //          Serial.println(packetBuffer);
    //          Serial.println(packetSize);

  }
}

