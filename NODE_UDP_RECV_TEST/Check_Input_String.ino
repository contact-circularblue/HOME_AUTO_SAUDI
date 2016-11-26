void Check_Input_String(String Check_Name)
{
  //Serial.print("Check_Name:");
  //Serial.println(Check_Name);   // Check_Name contains the contents of the packet

  if (Check_Name.substring(0, 10) == "jackhammer")
  {
    //Serial.println("I got it");
    //Serial.println(Check_Name.substring(11, 14));
    if (Check_Name.charAt(10) == "0")
    {

      Parse_State = Check_Name.substring(11, 14);
      //Serial.print("Parse_State is :");
      //Serial.println(Check_Name.substring(11, 14));

      if (Parse_State.charAt(0) >= 49 && Parse_State.charAt(0) <= 52)
      {
        if (Parse_State.charAt(2) == 48 || Parse_State.charAt(2) == 49)
        {
          Serial.print(Parse_State);
          //Serial.print("the node IP is: ");
          //UDP.remoteIP()="192.168.1.200";

          IPAddress Node_IP = WiFi.localIP();
          //Serial.println("Node_IP is: ");
          //Serial.println(Node_IP);

          /*
             ///////////////////////////////////////////add this fucntion at the end of IPAddress.cpp
            void IPAddress::getIP(String &ip_out){

            String s="";
            for (int i =0; i < 3; i++)
            {
            s+= String(_address.bytes[i], DEC);
            s+='.';
            }
            s+=String(_address.bytes[3], DEC);
            ip_out = s;
            }

            Add this prototype to IPAdderss.h
            void getIP(String &ip_out);
          */


          senders_ip = Node_IP.getIP();  //this function assigns the senders IP to String ip
          //Serial.print("ip = ");
          //Serial.println(ip);

          Octet_1 = senders_ip.substring(0, senders_ip.indexOf("."));
          //Serial.print("Octet_1 is:");
          //Serial.println(Octet_1);
          int x = Octet_1.length();
          //Serial.println(x);

          Temp_2 = senders_ip.substring(senders_ip.indexOf(".") + 1);
          Octet_2 = Temp_2.substring(0, senders_ip.indexOf("."));
          //Serial.print("Temp_2 is:");
          //Serial.println(Temp_2);
          //Serial.print("Octet_2 is:");
          //Serial.println(Octet_2);
          int y = Octet_2.length();
          //Serial.println(y);

          Temp_3 = Temp_2.substring(Temp_2.indexOf(".") + 1);
          Octet_3 = Temp_3.substring(0, Temp_3.indexOf("."));
          //        Serial.print("Temp_3 is:");
          //        Serial.println(Temp_3);
          //        Serial.print("Octet_3 is:");
          //        Serial.println(Octet_3);
          int z = Octet_3.length();
          //        Serial.println(z);

          Octet_4 = Temp_3.substring(Temp_3.indexOf(".") + 1);
          //        Serial.print("Octet_4 is:");
          //        Serial.println(Octet_4);
          int v = Octet_4.length();
          //        Serial.println(v);

          //        IPAddress IP_hub(Octet_1.toInt(), Octet_2.toInt(), Octet_3.toInt(), 200);

          IPAddress IP_hub2(Octet_1.toInt(), Octet_2.toInt(), Octet_3.toInt(), 200);
          IP_hub = IP_hub2;

          //        Serial.print("ip of hub is: ");

          // UDP.remoteIP() = IP_hub;

          //        Serial.print(IP_hub);


          //UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
          //UDP.beginPacket("192.168.1.200", UDP.remotePort());
          UDP.beginPacket(IP_hub, UDP.remotePort());

          UDP.write(ReplyBuffer);
          UDP.endPacket();
        }
      }
    }
    else
    {
      Serial.println("Request of IR Transmission");
    }
  }

}

