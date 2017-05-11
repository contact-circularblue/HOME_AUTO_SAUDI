#include <Arduino.h>

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

       Serial.print("WiFi_info= ");
       Serial.println(WiFi_info);

    int index = WiFi_info.indexOf("SSID:::password");
    if (index > -1)
    {

      String test_SSID = WiFi_info.substring(WiFi_info.indexOf("SSID:::password::") + 17, WiFi_info.indexOf("hub_pass"));
      String test_pass = WiFi_info.substring(WiFi_info.indexOf("hub_pass") + 9, WiFi_info.indexOf(":::END::"));

      Serial.println("test_SSID= " + test_SSID);
      Serial.println("test_pass= " + test_pass);

      String ID = "";
      int k = 0;
      int j = 0;
      for (int i = 0; i < test_SSID.length(); i++)
      {
        //ID += WiFi_info.charAt(i);
        ssid_1[i] = test_SSID.charAt(i);
        EEPROM.write(i + 1, ssid_1[i]); // saving the ssid
        delay(3);
        EEPROM.commit();
        k++;
        Serial.print(char(EEPROM.read(j + 1)));
      }
      Serial.println();
      EEPROM.write(0, k); // saving the length of ssid
      ssid_length = EEPROM.read(0); // saving the length of ssid
      delay(3);
      EEPROM.commit();

      Serial.print("SSID in EEPROM");

      k = 0;
      String pass = "";
      for (int i = 0; i < test_pass.length(); i++)
      {
        //ID += WiFi_info.charAt(i);
        password_1[i] = test_pass.charAt(i);
        EEPROM.write(i + 51, password_1[i]); // saving the ssid
        delay(3);
        EEPROM.commit();
        k++;
        Serial.print(char(EEPROM.read(j + 1)));
      }
      Serial.println();
      EEPROM.write(50, k); // saving the length of password
      delay(3);
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

