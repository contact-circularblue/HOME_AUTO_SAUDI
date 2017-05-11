void reconnect()
{
  // TURN OFF ALL STATUS LEDss
//  status_LEDs(2);

  // Loop until we're reconnected
  while (!client.connected()) {
    if(WiFi.status() != WL_CONNECTED)
    {
      break;
    }
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect

    if (client.connect(stringToCharArray(hub_id))) {
      Serial.println("connected");

      String para_template = "";
      para_template += hub_id;
      para_template += "/";

      String parameter = "";
      parameter += para_template;
      parameter += "inTopic";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "Node_power";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "Node_change";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "testTopic";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "wifi_details";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "add_Node";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "dummy";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "Node_IR_delete";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "addIRDevice";
      client.subscribe(stringToCharArray(parameter));
      client.loop();

      parameter = "";
      parameter += para_template;
      parameter += "wifi_details_rec";
      client.subscribe(stringToCharArray(parameter));
      client.loop();
    }

    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
