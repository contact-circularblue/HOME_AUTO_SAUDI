#include <Arduino.h>

void UDP_ACK_Switch()
{
  //Serial.println("Send ACK");
  IPAddress Node_IP = WiFi.localIP();

//            Serial.print("AP subnet mask: ");
            subnet = WiFi.subnetMask();
//            Serial.println(subnet);

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
            
  UDP.beginPacket(IP_hub, 80);
  UDP.write(ReplyBuffer);
  UDP.endPacket();
}
