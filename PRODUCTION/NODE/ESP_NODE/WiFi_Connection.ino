#include <Arduino.h>

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  char ssid[25] = "";
  char password[25] = "";



  for (int i = 51, j = 0; i < 51 + EEPROM.read(50); i++, j++)
  {
    password[j] = EEPROM.read(i);
  }

Serial.println("function");

String ssid_string="";

  for (int i = 1; i < EEPROM.read(0) + 1; i++)
  {
    ssid_string += char(EEPROM.read(i));
    Serial.print(ssid_string.charAt(i-1));
  }
  Serial.print("SSID:");
  Serial.println(ssid_string);

  for(int q=0;q<EEPROM.read(0);q++)
  ssid[q]=ssid_string.charAt(q);

  Serial.println("CONNECTING TO");
  Serial.print("SSID:");
  Serial.println(ssid);
  Serial.print("password:");
  Serial.println(password);

  WiFi.disconnect();
  delay(3000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 30)
    {
      state = false;
      if (EEPROM.read(200) == 1)
      {
        if(!Serial.available())
        {
        Serial.print("Resetting");
        ESP.reset();
        }
        else
        {
        get_details();
        }
      }
      break;
    }
    i++;
  }

  if (state)
  {
    state = true;
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
    state = false;
  }
  return state;
}
