#include <ESP8266WiFi.h>

const char *ssid =      "Circular Blue";      
const char *pass =      "mightycartoon";

// Update these with values suitable for your network.
IPAddress ip(192,168,1,200);  //Node static IP
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup()
{
 Serial.begin(115200); 
  WiFi.begin(ssid, pass);
  
  //Wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  WiFi.config(ip, gateway, subnet);
  Serial.print("working");
  
  Serial.println("");
  Serial.print("WiFi connected, using IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  delay(20);
}
