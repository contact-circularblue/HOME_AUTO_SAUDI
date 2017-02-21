void get_details()
{
  String WiFi_info = "";
  //  while (!Serial.available())
  //  {
  //    delay(1);
  //  }
  if (Serial.available())
  {
    while (Serial.available())
    {
      WiFi_info += char(Serial.read());
      delay(10);
    }
    delay(10);

//    Serial.print("WiFi_info= ");
//    Serial.println(WiFi_info);

    int index = WiFi_info.indexOf("SSID:");
    if (index > -1)
    {

      String test_SSID = WiFi_info.substring(WiFi_info.indexOf("SSID:") + 5, WiFi_info.indexOf("::PASSWORD::"));
      String test_pass = WiFi_info.substring(WiFi_info.indexOf("::password::") + 12, WiFi_info.indexOf(":::END:::"));

      Serial.println("test_SSID= " + test_SSID);
      Serial.println("test_pass= " + test_pass);

      String ID = "";
      int k = 0;
      int j = 0;
      for (int i = index + 5; i < WiFi_info.indexOf("::password::"); i++)
      {
        //ID += WiFi_info.charAt(i);
        ssid_1[j] = WiFi_info.charAt(i);
        EEPROM.write(j + 1, ssid_1[j]); // saving the ssid
        delay(10);
        EEPROM.commit();
        k++;
        Serial.print(char(EEPROM.read(j + 1)));
        j++;
      }
      EEPROM.write(0, k); // saving the length of ssid
      ssid_length = EEPROM.read(0); // saving the length of ssid
      delay(10);
      EEPROM.commit();

      Serial.print("SSID in EEPROM");

      String pass = "";
      int len = 0;
      for (int i = WiFi_info.indexOf("::password::") + 12, j = 0; i < WiFi_info.indexOf(":::END::"); i++, j++)
      {
        pass += WiFi_info.charAt(i);
        EEPROM.write(51 + j, pass.charAt(j)); // saving the password
        delay(10);
        EEPROM.commit();
        len++;
        Serial.println(char(EEPROM.read(51 + j)));
      }
      for (int i = 0; i < len; i++)
      {
        password_1[i] = pass.charAt(i);
      }

      EEPROM.write(50, len); // saving the length of password
      password_length = len;    // saving the length of password
      delay(10);
      EEPROM.commit();

      Serial.print("PASSWORD in EEPROM");

      Serial.println("SSID length");
      Serial.println(EEPROM.read(0));

      Serial.println("password length");
      Serial.println(EEPROM.read(50));

      EEPROM.write(200, 1);
      delay(10);
      EEPROM.commit();

      Serial.println("EEPROM Edited");

      //        connectWifi();
    }
  }
}

