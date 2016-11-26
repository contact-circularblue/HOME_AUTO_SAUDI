void Msg_from_switch()
{
  bool count = 0;
  while (Serial.available())
  {
    data_from_switch += char(Serial.read());
    count = 1;
  }

  if (count == 1)
  {
    if (data_from_switch.charAt(0) >= 49 && data_from_switch.charAt(0) <= 52)
    {
      if (data_from_switch.charAt(2) == 48 || data_from_switch.charAt(2) == 49)
      {
        Serial.println("data_from_switch is: ");
        Serial.println(data_from_switch);
      }
    }
    else
      Serial.println("invalid data send");

  }


  //  data_for_HUB+=Node_Name;
  //  data_for_HUB+=",";
  //  data_for_HUB+=data_from_switch;
  //
  //  Serial.println("data_for_HUB is: ");
  //  Serial.println(data_for_HUB);
  //
  //  data_for_HUB="";
  data_from_switch = "";

}






