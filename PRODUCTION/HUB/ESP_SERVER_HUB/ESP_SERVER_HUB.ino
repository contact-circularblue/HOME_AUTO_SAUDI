#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

/****HUB ID****/
String hub_id = "002";

/*DEFAULT WIFI ID PASSWORD*/

// char *ssid     = "samtech";
// char *password = "homeautomation";

char* ssid     = "Circular Blue";
char* password = "mightycartoon";

/*SERVER CONNECTION DETAILS*/
const char* mqtt_server = "104.131.44.88";
// const char* mqtt_server = "192.168.1.19";


/*OTHER VARIABLES*/
char buf[50];


/*PUBSUB CLIENT DECLARTIONS*/
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(9600);
  // client.setServer(mqtt_server, port_num);
  // client.setCallback(callback);

  /*INITIALIZE LED PINS AS OUTPUT*/
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);

  status_LEDs(0);

  /*INITIALIZE EEPROM*/
  EEPROM.begin(512);

  /*CHECK IF HUB IS ALREADY CONFIGURED*/
  if (EEPROM.read(200) == 1)
  {
    for (int i = 0; i <= EEPROM.read(0); i++)
    {
      ssid[i] = EEPROM.read(1 + i);
    }
    Serial.print("EEPROM_ssid_2 =");
    Serial.println(ssid);
    Serial.print("EEPROM_ssid_Length_2 =");
    Serial.println(EEPROM.read(0));


    for (int i = 0; i <= EEPROM.read(50); i++)
    {
      password[i] = EEPROM.read(51 + i);
    }
    Serial.print("EEPROM_password_2 =");
    Serial.println(password);
    Serial.print("EEPROM_password_Length_2 =");
    Serial.println(EEPROM.read(50));
  }

  /*CONNECT TO WiFi*/
  while (!connect_wifi())
  {
    delay(1);
    if (Serial.available())
    {
      delay(100);
      if (Serial.find("RESET_ESP"));
      EEPROM.write(200, 0);
      delay(10);
      EEPROM.commit();
      ESP.reset();
    }
  }

  /*TURN RED LED ON*/
  status_LEDs(1);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


}



void loop()
{
  if (!client.connected())
  {
    // TURN BLUE LED ON
    status_LEDs(2);
    reconnect();
    // TURN GREEN LED ON
    status_LEDs(3);
  }
  /*CHECK FOR ANY INCOMING MESSAGE*/
  client.loop();

  /*IF WiFi NOT CONNECTED THEN RECONNECT WiFi*/
  if (WiFi.status() != WL_CONNECTED) // IF WiFi disconnects, Reconnect WiFi
  {
    // TURN ALL LEDs OFFs
    status_LEDs(0);
    while (!connect_wifi());
    // TURN RED LED ON
    status_LEDs(1);

    if (!client.connected())
    {
      // TURN BLUE LED ON
      status_LEDs(2);
      reconnect();
      // TURN GREEN LED ON
      status_LEDs(3);
    }
  }

  /*CHECK IF SOMETHING CAME FROM THE ATMEGA*/
  String ATMEGA_INPUT = "";
  if (Serial.available())
  {
    // MAKE STRING FROM SERIAL REQUEST
    while (Serial.available())
    {
      ATMEGA_INPUT += char(Serial.read());
      delay(2);
    }
    
//    Serial.print("ATMEGA_INPUT:");
//    Serial.println(ATMEGA_INPUT);

    // IF REQUEST CAME FROM ANY NODE
    //    if (Buffer.indexOf("jackhammer,") != -1)
    //    {
    //      String from_node = "";
    //      int index = Buffer.indexOf("jackhammer,");
    //
    //      from_node = Buffer.substring(index + 11);
    //
    //      Serial.print("send_to_server=");
    //      Serial.println(from_node);
    //      send_to_server(from_node);
    //    } // REQUEST FROM NODE IF CONDITION END

    // IF REQUEST FOR RESET ARRIVED
    if (ATMEGA_INPUT.indexOf("RESET_ESP") != -1)
    {
      if (EEPROM.read(200) == 1)
      {
        EEPROM.write(200, 0);
        delay(100);
        EEPROM.commit();
        delay(100);
        Serial.print("EEPROM_RST= ");
        Serial.print(EEPROM.read(200));
        delay(500);
        ESP.reset();
      }
    } // RESET REQUEST IF CONDITION END

    else
      send_to_server(ATMEGA_INPUT);
  } // SERIAL CHECK IF CONDITION END
}
