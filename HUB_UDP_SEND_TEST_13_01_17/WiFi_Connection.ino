// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{

  Serial.print("Connecting to ");

  Serial.print(" ssid_1=");
  Serial.print(ssid_1);

  Serial.print("password_1=");
  Serial.print(password_1);

  WiFi.begin(ssid_1, password_1);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");

    Serial.println("");
    Serial.println("WiFi connected");

    delay(1000);

    Serial.print("WiFi connected, using IP address: ");
    Serial.println(WiFi.localIP());

    return true;
  }
}
