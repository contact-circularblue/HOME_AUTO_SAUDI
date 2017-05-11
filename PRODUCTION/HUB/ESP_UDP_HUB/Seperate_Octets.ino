#include <Arduino.h>

void seperate_octets(IPAddress subnet_local)//, int oct1, int oct2, int oct3, int oct4)
{
  String Octet_1 = "";
  String Octet_2 = "";
  String Octet_3 = "";
  String Octet_4 = "";

  
  String senders_ip = "";
  String Temp_1 = "";
  String Temp_2 = "";
  String Temp_3 = "";
  String Temp_4 = "";

  //  senders_ip = Node_IP.getIP();  //this function assigns the senders IP to String ip
  //  Serial.print("ip = ");
  //  Serial.println(senders_ip);

  senders_ip = subnet_local.getIP();

  Octet_1 = senders_ip.substring(0, senders_ip.indexOf("."));
//  Serial.print("Octet_1 is:");
//  Serial.println(Octet_1);
//  int x = Octet_1.length();
//  Serial.println(x);

  Temp_2 = senders_ip.substring(senders_ip.indexOf(".") + 1);
  Octet_2 = Temp_2.substring(0, senders_ip.indexOf("."));
//  Serial.print("Temp_2 is:");
//  Serial.println(Temp_2);
//  Serial.print("Octet_2 is:");
//  Serial.println(Octet_2);
//  int y = Octet_2.length();
//  Serial.println(y);

  Temp_3 = Temp_2.substring(Temp_2.indexOf(".") + 1);
  Octet_3 = Temp_3.substring(0, Temp_3.indexOf("."));
//  Serial.print("Temp_3 is:");
//  Serial.println(Temp_3);
//  Serial.print("Octet_3 is:");
//  Serial.println(Octet_3);
//  int z = Octet_3.length();
//  Serial.println(z);

  Octet_4 = Temp_3.substring(Temp_3.indexOf(".") + 1);
//  Serial.print("Octet_4 is:");
//  Serial.println(Octet_4);
//  int v = Octet_4.length();
//  Serial.println(v);
//
//Serial.println();
//Serial.println();

  octate1 = Octet_1.toInt();
//  Serial.println(oct1);
  octate2 = Octet_2.toInt();
//  Serial.println(oct2);
  octate3 = Octet_3.toInt();
//  Serial.println(oct3);
  octate4 = Octet_4.toInt();
//  Serial.println(oct4);
}
