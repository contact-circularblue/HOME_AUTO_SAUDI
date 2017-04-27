#include <Arduino.h>

bool UDP_ACK()
{
  int packetSize = UDP.parsePacket();

  if (packetSize)
  {
    UDP.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    //    Serial.println("Contents:");
    //    int value = packetBuffer[0]*256 + packetBuffer[1];
    String data_in_ack = "";
    for (int i = 0; i < packetSize; i++)
      data_in_ack += char(packetBuffer[i]);
    if (data_in_ack == "hub:jackhammer,ack")
      return true;

    else
    {
      //Serial.println("NO ACK");
      return false;
    }

  }
}




