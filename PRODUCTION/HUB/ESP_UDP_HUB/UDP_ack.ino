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

//    Serial.println("data_in:");
//    Serial.println(data_in_ack);
    
    StaticJsonBuffer<300> Buffer_ack;

    JsonObject& from_node = Buffer_ack.parseObject(data_in_ack);


    if (!from_node.success())
    {
      Serial.println("RECV parseObject() failed");
      return false;
    }

    String success = from_node[String("s")];
//    Serial.print("success = ");
//    Serial.println(success);

 
    {
      String nId = from_node[String("nId")];
      String dId = from_node[String("dId")];
      String ACK = from_node[String("ACK")];
      String REQ = from_node[String("REQ")];
      String VAL = from_node[String("VAL")];

      if (ACK == "T")
      {
//        Serial.println("data_in_ack:");
        Serial.print(data_in_ack);
        return true;
      }

      else if (ACK == "F")
      {
        Serial.print(data_in_ack);
        return false;
      }
    }




    //    if (data_in_ack == "hub:jackhammer,ack")
    //      return true;
    //
    //    else
    //    {
    //      //Serial.println("NO ACK");
    //      return false;
    //    }

  }
}




