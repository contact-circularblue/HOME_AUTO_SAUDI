#include <Arduino.h>

void Check_Input_String(String Check_Name)
{
  StaticJsonBuffer<300> Buffer;

  //   Serial.print("Check_Name:");
  //   Serial.println(Check_Name);   // Check_Name contains the contents of the packet

  JsonObject& from_hub = Buffer.parseObject(Check_Name);
  String success = from_hub[String("s")];

  if (!from_hub.success())
  {
    Serial.println("parseObject() failed");
    return;
  }

  if (success == "t" && from_hub[String("nId")] == Node_Name)
  {
    String dId = from_hub[String("dId")];
    String ACK = from_hub[String("ACK")];
    String REQ = from_hub[String("REQ")];
    String VAL = from_hub[String("VAL")];



    //Serial.println("I got it");
    //Serial.println(Check_Name.substring(11, 14));
    Parse_State = Check_Name.substring(11, 16);
    //    Serial.print("Parse_State is :");
    //    //Serial.println(Check_Name.substring(11, 14));
    //Serial.println(Parse_State);
    String req_from_hub = "";
    req_from_hub += REQ + ',' + dId + ',' + VAL;
    Serial.print(req_from_hub);

    //ACK_THE_HUB();

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
    StaticJsonBuffer<300> Buffer_hub_ack;
    
    JsonObject& hub_ack = Buffer_hub_ack.createObject();

    hub_ack["nId"] = Node_Name;
    hub_ack["s"] = String("t");
    hub_ack["ACK"] = "T";
    hub_ack["REQ"] = REQ;
    hub_ack["dId"] = dId;
    hub_ack["VAL"] = VAL;

    String json_hub_ack = "";
    hub_ack.printTo(json_hub_ack);
    
//    Serial.println("json_hub_ack="+json_hub_ack);

    char json_hub_ack_chars[100];
    stringToCharArray(json_hub_ack, json_hub_ack_chars);

    UDP.beginPacket(IP_hub, 80);
    UDP.write(json_hub_ack_chars);
    UDP.endPacket();
    
//    Serial.println("ACK:");
//    Serial.println(json_hub_ack_chars);
  }
}
