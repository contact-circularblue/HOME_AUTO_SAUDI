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

//char *ssid     = "samtech";
//char *password = "homeautomation";

//char* ssid     = "iPhone";
//char* password = "ambition";

char* ssid     = "Circular Blue";
char* password = "mightycartoon";

char host[] = "104.131.44.88";
//char host[] = "192.168.1.143";
int port = 3000;

extern bool socket_connected;
extern int flag;

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
const long interval = 900000;           // interval at which to send dummy packet


String json_add_hub = "";
String json_add_node = "";
void setup() {

  /*
     4->RED
     2->BLUE
     12->GREEN
     14->YELLOW
  */

  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  status_LEDs(0);

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
  status_LEDs(1);



  while (!connect_to_server());
  status_LEDs(2);


  while (!connect_socket());

  // Serial.println("SOCKET CONNECTED NOW");
  //client.send("connection", "message", "Connected !!!!");

  delay(100);
  monitor_client();/// The server has returned message="connected". Just read it out of the buffer.



  add_hub();
  status_LEDs(3);

  client.monitor();

  Serial.println(ESP.getResetReason());

  //Serial.println("hum yahaan hain!");

}

void loop()
{

  //client.send("wifi", "message", "success");
  delay(10);

if(WiFi.status() != WL_CONNECTED) // IF WiFi disconnects, Reconnect WiFi
{
  while (!connect_wifi());
  status_LEDs(1);



  while (!connect_to_server());
  status_LEDs(2);


  while (!connect_socket());

  // Serial.println("SOCKET CONNECTED NOW");
  //client.send("connection", "message", "Connected !!!!");

  delay(100);
  monitor_client();/// The server has returned message="connected". Just read it out of the buffer.



  add_hub();
  status_LEDs(3);

  client.monitor();  
}


if (flag == 1) // IF server disconnects, Reconnect to Server
  {
    status_LEDs(1);
    while (!connect_to_server());
    status_LEDs(2);


    while (!connect_socket());
    // Serial.println("SOCKET CONNECTED NOW");
    //client.send("connection", "message", "Connected !!!!");

    delay(100);
    monitor_client();/// The server has returned message="connected". Just read it out of the buffer.

    add_hub();
    status_LEDs(3);
    client.monitor();

    flag = 0;
  }

  

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
      Serial.print("send_to_server=");
      Serial.println(from_node);
      while (Serial.available())
        Serial.read();
      send_to_server(from_node);
    }
  }




  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    client.heartbeat(3); //Send Pong
    client.monitor();
  }

}


