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

//char* ssid     = "SIDHARTH-Network";
//char* password = "Dominos1";

char* ssid     = "Circular Blue";
char* password = "mightycartoon";

//char host[] = "104.131.44.88";
//char host[] = "104.131.44.88";
char host[] = "192.168.1.9";
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
const long interval = 2000;           // interval at which to send dummy packet

void setup() {
  Serial.begin(9600);
  delay(10);

  // We start by connecting to a WiFi network
  while (!connect_wifi());

 

  while (!connect_to_server());


  while (!connect_socket());
  Serial.println("SOCKET CONNECTED NOW");
  //client.send("connection", "message", "Connected !!!!");

  delay(100);
  monitor_client();/// The server has returned message="connected". Just read it out of the buffer.


  add_hub();
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

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    client.send("dummy", "message", "1");

    ////when there is any change at the node
    //JsonObject& root = jsonBuffer.createObject();
    //  root["nodeId"] = "4234567890";
    //  root["deviceId"] = 1;
    //  root["deviceState"] = 0;
    //  String json = "";
    //  root.printTo(json);
    //
    //client.sendJSON("Node_change", json);

  }
  //delay(100);
}


