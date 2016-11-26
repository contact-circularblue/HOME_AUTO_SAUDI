bool connect_wifi()//String ssid, String password)
{
  bool state = true;
  int i=0;
  Serial.println(ssid);
  Serial.println(password);
  
  WiFi.begin(ssid,password);
  
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
