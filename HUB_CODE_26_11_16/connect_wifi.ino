bool connect_wifi(char* ssid1, char* password1)
{
  bool state = true;
  int i=0;
  Serial.println(ssid1);
  Serial.println(password1);
//  WiFi.disconnect();
//  delay(1000);
  WiFi.begin(ssid1,password1);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
state = false;
break;
}
i++;
  }
  
  if(state)
  {
   Serial.println("");
  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
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
