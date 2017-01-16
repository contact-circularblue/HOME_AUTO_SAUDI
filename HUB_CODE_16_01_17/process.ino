void process()
{

  if (RID != "")
  {
    if (RID == "wifi_details")
    {
      Serial.print("RID= ");
      Serial.println(RID);

      ARD_JSON(Rcontent);

      for (int i = 0; i <= data0_val.length(); i++)
      {
        EEPROM.write(1 + i, data0_val[i]);
        ssid[i] = EEPROM.read(1 + i);
      }
      Serial.print("EEPROM_ssid_1 =");
      Serial.println(ssid);
      EEPROM.write(0, data0_val.length());
      Serial.print("EEPROM_ssid_Length_1 =");
      Serial.println(EEPROM.read(0));


      for (int i = 0; i <= data1_val.length(); i++)
      {
        EEPROM.write(51 + i, data1_val[i]);
        password[i] = EEPROM.read(51 + i);
      }
      Serial.print("EEPROM_password_1 =");
      Serial.println(password);
      EEPROM.write(50, data1_val.length());
      Serial.print("EEPROM_pass_Length_1 =");
      Serial.println(EEPROM.read(50));

      WiFi.disconnect();
      status_LEDs(0);
      delay(1000);

      while (WiFi.status() == WL_CONNECTED);
      //Serial.println("DISCONNECTED");

      delay(3000);

      while (!connect_wifi());

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

        while (!connect_to_server());


        while (!connect_socket());
        status_LEDs(2);

        delay(100);

        monitor_client();/// The server has returned message="connected". Just read it out of the buffer");

        delay(1000);

        //        Serial.println("client monitoring complete");
        add_hub();
        status_LEDs(3);

        //        Serial.println("hub add complete");

        delay(100);
        Serial.print("Sending ACK\n");
        client.send("wifi_details_rec", "message", "success");

        delay(100);

      }
    }
    else if (RID == "add_Node")
    {
      status_LEDs(4);
      Serial.println("Adding Node");
      delay(10);

      Serial.print("Sending json= ");
      Serial.println(json_add_node);
      client.sendJSON("add_Node", json_add_node);
      Serial.print("JSON sent");


      delay(3000);
      status_LEDs(5);
    }


    else if (RID == "dummy")
    {
      Serial.println("Dummy reply ID= " + RID);
      //client.send("dummy", "message", "1");
    }

    //    else if (RID == "message")
    //    {
    ////      Serial.println("check_alive");
    ////      delay(10);
    ////      client.send("check_alive", "message", "1");
    ////      delay(10);
    ////      client.send("dummy", "message", "1");
    //
    //Serial.println("sent dummy");
    //client.send("message", "message", "1");
    ////      Serial.println("Sent Replies");
    //    }

    else if (RID == "check_alive")
    {
      Serial.println("check_alive");

      client.reconnect_socket();
    }

    else if (RID == "Node_power")
    {
      Serial.print("hub_says:");
      Serial.print("jackhammer,"); ////NODE ID for example
      Serial.print("0"); //// NODE CHANGE FOR SWITCHES
      Serial.print(",");
      Serial.print("30");
      Serial.print(",");
      Serial.print("0");



      //      int power = 198;
      //      JsonObject& root = jsonBuffer.createObject();

      //      root["nId"] = String(nodeId);
      //      root["power"] = String(power);
      //      String json = "";
      //      root.printTo(json);
      //      //      Serial.print("Sending json= ");
      //      //      Serial.println(json);
      //      client.sendJSON("Node_power", json);
    }

    else if (RID == "Node_change")
    {
      //      Serial.println("Node_change requested");
      //      Serial.println("nodeId= " +nodeId +"deviceId=" +deviceId +"deviceState=" +deviceState);

      JsonObject& root = jsonBuffer.createObject();

      root["nId"] = String(nodeId);
      root["dId"] = String(deviceId);
      root["dState"] = String(deviceState);
      String json = "";
      root.printTo(json);
      Serial.print("Sending json= ");
      Serial.println(json);
      client.sendJSON("Node_change", json);

      //Serial.println();
      Serial.print("hub_says:");
      Serial.print("jackhammer,"); ////NODE ID for example
      Serial.print("0"); //// NODE CHANGE FOR SWITCHES
      Serial.print(",");
      Serial.print(deviceId);
      Serial.print(",");
      if (deviceState == "true")
        Serial.print("1");
      else if (deviceState == "false")
        Serial.print("0");
      //Serial.println();


      //      delay(3000);
      //
      //      JsonObject& root2 = jsonBuffer.createObject();
      //
      //      root2["nId"] = String(nodeId);
      //      root2["dId"] = String(deviceId);
      //      root2["dState"] = String("false");
      //      String json2 = "";
      //      root2.printTo(json2);
      //      Serial.print("Sending json= "  + json2);
      //      client.sendJSON("Node_change", json2);


    }

    else if (RID == "ack")
    {

    }

    else if (RID == "Node_IR_delete")
    {
      Serial.print("hub_says:");
      Serial.print("jackhammer,"); ////NODE ID for example
      Serial.print("2"); //// NODE CHANGE FOR SWITCHES
      Serial.print(",");
      Serial.print(deviceId);
      Serial.print(",");
      Serial.print("0");

      JsonObject& root = jsonBuffer.createObject();

      root["success"] = String("true");
      root["nId"] = String(nodeId);
      root["dId"] = String(deviceId);
      String json = "";
      root.printTo(json);
      //      Serial.print("Sending json= ");
      //      Serial.println(json);
      client.sendJSON("Node_IR_delete", json);
    }

    else if (RID == "addIRDevice")
    {

      Serial.println("RID= addIRDevice");
      Serial.println("success=" + data0_val);
      Serial.println("nId=" + data1_val);

      //delay(3000);

      JsonObject& root = jsonBuffer.createObject();


      //      String deviceId = "5";
      //
      //      root["success"] = String(data0_val);
      //      root["nId"] = String(data1_val);
      //      root["dId"] = String(deviceId);
      //      String json = "";
      //      root.printTo(json);
      //      //      Serial.print("Sending json= ");
      //      //      Serial.println(json);
      //      client.sendJSON("addIRDevice", json);

      Serial.print("hub_says:");
      Serial.print("jackhammer,"); ////NODE ID for example
      Serial.print("1"); //// NODE CHANGE FOR IR ADD
      Serial.print(",");
      Serial.print("0");
      Serial.print(",");
      Serial.print("0");

      delay(100);
      //      while (!Serial.find("jackhammer,"))
      //      {
      //        delay(100);
      //
      //      }
      //
      ////      Serial.println("found jackhammer,");
      //      delay(100);
      //      String from_node = "";
      //      while (Serial.available())
      //      {
      //        //Serial.print(char(Serial.read()));
      //        from_node += (char(Serial.read()));
      //        delay(10);
      //      }
      ////      Serial.println("from_node=" + from_node);
      //
      //      send_to_server(from_node);
    }

    else
    {
      Serial.println("RID NOT FOUND");
    }
  }
}
