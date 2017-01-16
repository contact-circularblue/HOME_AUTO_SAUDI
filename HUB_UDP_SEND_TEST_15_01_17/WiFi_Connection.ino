// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  char ssid_2[25] = "";
  char password_2[25] = "";
  bool state = true;
  int i = 0;

  Serial.print("Connecting to ");

  for (int i = 1; i < EEPROM.read(0) + 1; i++)
  {
    ssid_2[i - 1] = EEPROM.read(i);
    //delay(10);
  }

  for (int i = 51, j = 0; i < 51 + EEPROM.read(50); i++, j++)
  {
   // password_2[j] = EEPROM.read(i);
    //delay(10);
  }


  Serial.print("ssid_2=");
  Serial.println(ssid_2);

  Serial.print("password_2=");
  Serial.println(password_2);

  WiFi.disconnect();

  delay(3000);

  WiFi.begin(ssid_2, password_2);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false;
      Serial.print("Resetting");
      ESP.reset();
    }
    i++;
  }

  if (state)
  {
    Serial.println("");
    Serial.println("WiFi connected");

    delay(1000);

    Serial.print("WiFi connected, using IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
    return false;
  }

}

