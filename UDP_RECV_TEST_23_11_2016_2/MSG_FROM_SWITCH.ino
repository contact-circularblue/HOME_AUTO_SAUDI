void Msg_from_switch()
{
  bool count = 0;
  while (Serial.available())
  {
    data_from_switch += char(Serial.read());
    count = 1;
    delay(50);
  }

  if (count == 1)
  {
    if (data_from_switch.charAt(0) >= 49 && data_from_switch.charAt(0) <= 52)
    {
      if (data_from_switch.charAt(2) == 48 || data_from_switch.charAt(2) == 49)
      {
        // Serial.println("data_from_switch is: ");
        Serial.println(data_from_switch);

        data_for_HUB += Node_Name;
        data_for_HUB += ",";
        data_for_HUB += data_from_switch;

        Serial.println("data_for_HUB is: ");
        Serial.println(data_for_HUB);
      }
    }
  }

  
  //UDP.beginPacket(IP_hub, UDP.remotePort());
  UDP.beginPacket("192.168.1.200", UDP.remotePort());
  char* data_for_HUB_local="";
  data_for_HUB.toCharArray(data_for_HUB_local, data_for_HUB.length() + 1);
  UDP.write(data_for_HUB_local);
  UDP.endPacket();
  //Serial.print("message send");

  data_from_switch = "";
  data_for_HUB = "";
}






