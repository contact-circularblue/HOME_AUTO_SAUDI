#include <Arduino.h>

void ARD_JSON(String a, char* topic)
{


  StaticJsonBuffer<300> jsonBuffer;
  StaticJsonBuffer<300> hub_Buffer;

  // Serial.print("json from server =");
  // Serial.println(a);

  JsonObject& root = jsonBuffer.parseObject(a);

  JsonObject& hub_msg = hub_Buffer.createObject();

  if (!root.success())
  {
    Serial.println("parseObject() failed");
    return;
  }

  String success_local = root[String("success")];
  String I_local = root[String("I")];
  // Serial.print("success= ");
  // Serial.println(success_local);

  if (success_local == "true" && I_local != "Y")
  {
    JsonObject& root2 = jsonBuffer.createObject();

    String nId = root[String("nId")];
    root2["nId"] = nId;
    hub_msg["nId"] = nId;
    hub_msg["s"] = String("t");




    /* SERVICES */

    //NODE POWER
    String topic_local = hub_id + "/" + "Node_power";
    if (0 == strcmp(topic, stringToCharArray(topic_local))) //i.e if the incoming topic is equal to the required topic
    {
      //Serial.print("hub_says:");
      hub_msg["ACK"] = "F";
      hub_msg["REQ"] = "0";
      hub_msg["dId"] = "30";
      hub_msg["VAL"] = "0";

      String json_hub_msg = "";
      hub_msg.printTo(json_hub_msg);

      Serial.print(json_hub_msg);

      // Serial.print("jackhammer,"); ////NODE ID for example
      // Serial.print("0");
      // Serial.print(",");
      // Serial.print("30");
      // Serial.print(",");
      // Serial.print("0");
    }





    //NODE CHANGE
    topic_local = "";
    topic_local = hub_id + "/" + "Node_change";
    if (0 == strcmp(topic, stringToCharArray(topic_local)))
    {
      String ID = root[String("dId")];
      String state = root[String("dState")];

      //Serial.print("hub_says:");

      hub_msg["ACK"] = "F";
      hub_msg["REQ"] = "0";
      hub_msg["dId"] = ID;
      if (state == "true")
        hub_msg["VAL"] = "1";
      else if (state == "false")
        hub_msg["VAL"] = "0";

      String json_hub_msg = "";
      hub_msg.printTo(json_hub_msg);

      Serial.print(json_hub_msg);

      // Serial.print("hub_says:");
      // Serial.print("jackhammer,"); ////NODE ID for example
      // Serial.print("0"); //// NODE CHANGE FOR SWITCHES
      // Serial.print(",");
      // Serial.print(ID);
      // Serial.print(",");
      // if (state == "true")
      //   Serial.print("1");
      // else if (state == "false")
      //   Serial.print("0");



      //      root2["dId"] = ID;
      //      root2["dState"] = state;
      //      String json2 = "";
      //      root2.printTo(json2);
      //      client.publish(topic, stringToCharArray(json2));
    }





    //WiFi DETAILS
    topic_local = "";
    topic_local = hub_id + "/" + "wifi_details";
    if (0 == strcmp(topic, stringToCharArray(topic_local)))
    {
      Serial.println("WiFi details received");


      String message_local = root[String("message")];
      Serial.print("message_local= ");
      Serial.println(message_local);

      String data0 = root["message"][0];
      Serial.println(data0);

      String data1 = root["message"][1];
      Serial.println(data1);


      for (int i = 0; i <= data0.length(); i++)
      {
        EEPROM.write(1 + i, data0.charAt(i));
        ssid[i] = EEPROM.read(1 + i);
      }

      Serial.print("EEPROM_ssid_1 =");
      Serial.println(ssid);
      EEPROM.write(0, data0.length());
      Serial.print("EEPROM_ssid_Length_1 =");
      Serial.println(EEPROM.read(0));


      for (int i = 0; i <= data1.length(); i++)
      {
        EEPROM.write(51 + i, data1.charAt(i));
        password[i] = EEPROM.read(51 + i);
      }
      Serial.print("EEPROM_password_1 =");
      Serial.println(password);
      EEPROM.write(50, data1.length());
      Serial.print("EEPROM_pass_Length_1 =");
      Serial.println(EEPROM.read(50));

      WiFi.disconnect();
      status_LEDs(0);
      delay(1000);

      while (WiFi.status() == WL_CONNECTED);
      //Serial.println("DISCONNECTED");

      delay(3000);

      for (int i = 0; i < 3; i++)
      {

        WiFi.begin(ssid, password);
        int j = 0;
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");

          if (j > 20) {
            break;
          }
          j++;
        }
        if (WiFi.status() == WL_CONNECTED)
          break;
        else if (i == 2)
        {
          Serial.print("HUB UNABLE TO CONNECT");
          while (1)
          {
            delay(100);
          }
        }
      }

      EEPROM.write(200, 1); // flag to indicate wifi connction successful
      delay(100);
      EEPROM.commit();
      Serial.print("EEPROM= ");
      Serial.println(EEPROM.read(200));

      // for(int i=0; i<ssid.length;i)

      if (WiFi.status() == WL_CONNECTED)
      {
        status_LEDs(1);
        //Serial.println("wifi connected");

        if (!client.connected())
        {
          // TURN BLUE LED ON
          status_LEDs(2);
          reconnect();
          // TURN GREEN LED ON
          status_LEDs(3);
        }

        //        Serial.println("hub add complete");

        delay(100);
        //        Serial.print("Sending ACK\n");

        // Send WiFi details to the other ESP

        while (1)
        {
          Serial.print("details:");
          Serial.print(ssid);
          Serial.print("hub_pass:");
          Serial.print(password);
          Serial.print("::::end");

          delay(2000);

          if (Serial.find("WIFI_ACK"))
          {

            String topic_wifi_ack = hub_id + "/" + "wifi_details_rec";
            Serial.println("topic_wifi_ack=" + topic_wifi_ack);

            char tem1[50];
            char tem2[50];
            client.publish(stringToCharArray(topic_wifi_ack, tem1), stringToCharArray(String("success"), tem2));
            break;
          }
        }
      }
    }









    //ADD NODE
    topic_local = "";
    topic_local = hub_id + "/" + "add_Node";
    if (0 == strcmp(topic, stringToCharArray(topic_local)))
    {
      status_LEDs(4);
      Serial.println("node_add:");
      delay(6000);

      //            while(Serial.available())
      //            Serial.print(char(Serial.read()));


      String ID = "";
      {
        ID = "";
        if (Serial.available())
        {
          while (Serial.available())
          {
            ID += char(Serial.read());
            delay(10);
          }
          Serial.println("ID_STRING= " + ID);
        }
      }

      delay(1000);

      Serial.println("1");

      for (int i = 0; i < 50; i++)
      {
        if (ID.indexOf("ID:") != -1)
        {

          Serial.println("2");

          String node_ID = ID.substring(ID.indexOf("ID:") + 3);
          // json_add_node = "";

          //String node_Id = "4234567890";

          Serial.println("3");

          JsonObject& root_add_node = jsonBuffer.createObject();

          // String node_ID="4234567890";
          root_add_node["nodeId"] = node_ID;
          root_add_node["type"] = String(node_ID[0]);
          String json_root_add_node = "";
          root_add_node.printTo(json_root_add_node);
          client.publish(topic, stringToCharArray(json_root_add_node));

          break;
        }

        delay(200);

      }
      status_LEDs(5);
    }







    //IR DELETE
    topic_local = "";
    topic_local = hub_id + "/" + "Node_IR_delete";
    if (0 == strcmp(topic, stringToCharArray(topic_local)))
    {
      String ID = root[String("dId")];
      root2["dId"] = ID;

      hub_msg["ACK"] = "F";
      hub_msg["REQ"] = "2";
      hub_msg["dId"] = ID;
      hub_msg["VAL"] = "0";

      String json_hub_msg = "";
      hub_msg.printTo(json_hub_msg);

      Serial.print(json_hub_msg);

      // Serial.print("hub_says:");
      // Serial.print("jackhammer,"); ////NODE ID for example
      // Serial.print("2"); //// NODE CHANGE FOR SWITCHES
      // Serial.print(",");
      // Serial.print(deviceId);
      // Serial.print(",");
      // Serial.print("0");

      root2["s"] = String("t");
      String json2 = "";
      root2.printTo(json2);
      client.publish(topic, stringToCharArray(json2));
    }






    //IR ADD
    topic_local = "";
    topic_local = hub_id + "/" + "addIRDevice";
    if (0 == strcmp(topic, stringToCharArray(topic_local)))
    {
      hub_msg["ACK"] = "F";
      hub_msg["REQ"] = "1";
      hub_msg["dId"] = "0";
      hub_msg["VAL"] = "0";

      String json_hub_msg = "";
      hub_msg.printTo(json_hub_msg);

      Serial.print(json_hub_msg);

      // Serial.print("hub_says:");
      // Serial.print("jackhammer,"); ////NODE ID for example
      // Serial.print("1"); //// NODE CHANGE FOR IR ADD
      // Serial.print(",");
      // Serial.print("0");
      // Serial.print(",");
      // Serial.print("0");
    }

    /* END OF SERVICES */

  } // END OF IF CONDITION FOR SUCCESS CHECK
}
