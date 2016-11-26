void Msg_from_switch()
{
  if (Serial.available())
  {
    data_from_switch = "";
    data_for_HUB = "";
    Serial.println("Initially:");
    Serial.print("data from ARDUINO: " + data_from_switch);
    Serial.println();

    while (Serial.available())
    {
      data_from_switch += char(Serial.read());
      delay(10);
    }
    Serial.print("data from ARDUINO: " + data_from_switch);

    Serial.println();

    if (data_from_switch.charAt(0) == 48)
    {
            
      if (data_from_switch.charAt(2) >= 49 && data_from_switch.charAt(2) <= 52)
      {
        if (data_from_switch.charAt(4) == 48 || data_from_switch.charAt(4) == 49)
        {
          Serial.print("data_from_switch is: ");
          Serial.print(data_from_switch);
          Serial.println();

          data_for_HUB += Node_Name;
          data_for_HUB += ",";
          data_for_HUB += data_from_switch;

          Serial.print("data_for_HUB is: " + data_for_HUB);
          Serial.println();

          IPAddress hub_ip_fn(192, 168, 1, 200);


          ////////Send data to HUB
          UDP.beginPacket(hub_ip_fn, 80);
          char data_for_HUB_local [25];

          convert_to_char(data_for_HUB, data_for_HUB_local);

          UDP.write(data_for_HUB_local);
          UDP.endPacket();


          data_from_switch = "";
          data_for_HUB = "";

        }
      }
    }
    else if(data_from_switch.charAt(0) == 49)
    {
      Serial.print("Request of IR Transmission from switch");
    }
  }
}






