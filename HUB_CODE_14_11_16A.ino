/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h>



StaticJsonBuffer<200> jsonBuffer;

SocketIOClient client;
const char* ssid     = "Circular Blue";
const char* password = "mightycartoon";

char host[] = "192.168.1.5";
int port = 3000;

extern String rcvd_msg_full;

extern String RID;
extern String Rname;
extern String Rcontent;

String message = "message";
String success = "success";
String message_val = "";
String success_val = "";

unsigned long previousMillis = 0;
long interval = 5000;
unsigned long lastreply = 0;
unsigned long lastsend = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }
  if (client.connected())
  {
    Serial.println("CONNECTED NOW");
    //client.send("connection", "message", "Connected !!!!");
    
    Serial.println("CSending device type");
    client.send("DeviceType", "message", "Hub");
    delay(100);
    Serial.println("Sending new device ID");
    client.send("new user", "message", "1234");
    
  }

}

void loop() {

//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > interval)
  {
   // previousMillis = currentMillis;
    //client.heartbeat(0);
    
    
    //lastsend = millis();
  }
  if (client.monitor())
  {

    //    Serial.println("MONITOR");
    //    lastreply = millis();
    if (RID != "")
    {
      Serial.print("RID= ");
      Serial.println(RID);


      Serial.print("Rname= ");
      Serial.println(Rname);

      //    Serial.print("Rcontent= ");
      //    Serial.println(Rcontent);

      parse_json(Rcontent);
    }


    //      Serial.print("MESSAGE= ");
    //      Serial.println(rcvd_msg_full);
  }

}

void parse_json(String in)
{
  success_val = in.substring(15, in.indexOf("\\\","));
  message_val = in.substring((in.indexOf("message") + 12), in.indexOf("\\\"}"));
  Serial.print("success= ");
  Serial.println(success_val);
  Serial.print("message= ");
  Serial.println(message_val);

}

