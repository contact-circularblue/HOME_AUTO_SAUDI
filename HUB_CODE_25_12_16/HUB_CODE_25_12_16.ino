/*
    This sketch sends data via HTTP GET requests to data.sparkfun.com service.

    You need to get streamId and privateKey at data.sparkfun.com and paste them
    below. Or just customize this script to talk to other HTTP servers.

*/
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h>



DynamicJsonBuffer jsonBuffer;

SocketIOClient client;

//char ssid[25]     = "attack";
//char password[25] = "attacker";

//char* ssid     = "iPhone";
//char* password = "ambition";

char* ssid     = "Circular Blue";
char* password = "mightycartoon";

//char host[] = "104.131.44.88";
char host[] = "192.168.1.12";
int port = 3000;

extern bool socket_connected;

extern String rcvd_msg_full;
extern String RID;
extern String Rname;
extern String Rcontent;

String message = "message";
String success = "success";
String message_val = "";
//String message_val_t = "";
String success_val = "";
String data0_val = "";
String data1_val = "";
String nodeId = "";
String deviceId = "";
String deviceState = "";

bool hub_connected = false;


//unsigned long previousMillis = 0;
//long interval = 5000;
//unsigned long lastreply = 0;
//unsigned long lastsend = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 25000;           // interval at which to send dummy packet


String json_add_hub = "";
String json_add_node = "";
void setup() {

  String node_Id = "4234567890";

  JsonObject& root_add_node = jsonBuffer.createObject();
  root_add_node["nodeId"] = node_Id;
  root_add_node["type"] = String(node_Id[0]);
  
  root_add_node.printTo(json_add_node);

  JsonObject& root_hub_add = jsonBuffer.createObject();
  struct DeviceType_ {
    String Hub = "Hub";
  } DeviceType;

  root_hub_add["deviceType"] = DeviceType.Hub;
  root_hub_add["uniqueID"] = "1234";


  //    Serial.print("printing to string");
  root_hub_add.printTo(json_add_hub);

  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  while (!connect_wifi());



  while (!connect_to_server());


  while (!connect_socket());
  // Serial.println("SOCKET CONNECTED NOW");
  //client.send("connection", "message", "Connected !!!!");

  delay(100);
  monitor_client();/// The server has returned message="connected". Just read it out of the buffer.



  add_hub();

  
Serial.println(ESP.getResetReason());

  //Serial.println("hum yahaan hain!");

}

void loop()
{

  //client.send("wifi", "message", "success");
  delay(10);



  if (monitor_client())
  {
    process();
  }

  if (Serial.available())
  {
    delay(50);
    if (Serial.find("jackhammer,"))
    {
      String from_node = "";
      while (Serial.available())
      {
        from_node += (char(Serial.read()));
        delay(10);
      }

      send_to_server(from_node);
    }
  }

  


  unsigned long currentMillis = millis();

//  Serial.print("currentMillis - previousMillis= ");
//  Serial.println(currentMillis - previousMillis);

  if (currentMillis - previousMillis >= interval) 
  {
//    Serial.print("Available heap=");
//    Serial.println(ESP.getFreeHeap());
//    previousMillis = currentMillis;
//
    client.heartbeat(1);
    delay(10);
    client.monitor();
previousMillis = currentMillis;

//Serial.println("sent dummy");
//client.send("dummy", "message", "1");

  }
  
}


