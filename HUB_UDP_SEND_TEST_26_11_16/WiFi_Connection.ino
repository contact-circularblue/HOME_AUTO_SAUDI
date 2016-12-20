// connect to wifi – returns true if successful or false if not
boolean connectWifi() {


  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  delay(1000);
  //IPAddress ip(192, 168, 1, 200); //Node static IP
  //IPAddress gateway(192, 168, 1, 1);
  //IPAddress subnet(255, 255, 255, 0);
  //Serial.print("Static IP=");
  //Serial.println(ip);
  //Serial.print("gateway=");
  //Serial.println(gateway);
  //Serial.print("subnet=");
  //Serial.println(subnet);
  //
  //  WiFi.config(ip, gateway, subnet);
  //    Serial.print("working");

  //    Serial.println("");
  Serial.print("WiFi connected, using IP address: ");
  Serial.println(WiFi.localIP());

  return true;

  //  ssid = "Circular Blue";
  //password = "mightycartoon";
  //
  //  boolean state = true;
  //  int i = 0;
  //  WiFi.begin(ssid, password);
  ////  Serial.println("");
  //Serial.println("Connecting to WiFi");
  //
  //  // Wait for connection
  ////  Serial.print("Connecting");
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  // Serial.print(".");
  //    if (i > 10) {
  //      state = false;
  //      break;
  //    }
  //    i++;
  //  }
  //  if (state) {
  //    Serial.println("");
  //    Serial.print("Connected to ");
  //    Serial.println(ssid);
  //    Serial.print("IP address: ");
  //    Serial.println(WiFi.localIP());
  //
  //    WiFi.config(ip, gateway, subnet);
  ////    Serial.print("working");
  //
  ////    Serial.println("");
  //    Serial.print("WiFi connected, using IP address: ");
  //    Serial.println(WiFi.localIP());
  //  }
  //  else {
  //    Serial.println("");
  //    Serial.println("Connection failed.");
  //  }
  //  return state;
}
