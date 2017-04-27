void reconnect()
{
  // TURN OFF ALL STATUS LEDss
  status_LEDs(0);

  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("002")) {
      Serial.println("connected");

      String para_template="";
      para_template+=hub_id;
      para_template+="/";

      String parameter="";
      parameter+=para_template;
      parameter+="inTopic";


      client.subscribe(stringToCharArray(parameter));
      client.loop();
      client.subscribe("002/Node_power");
      client.loop();
      client.subscribe("002/Node_change");
      client.loop();
      client.subscribe("002/testTopic");
      client.loop();
      client.subscribe("002/wifi_details");
      client.loop();
      client.subscribe("002/add_Node");
      client.loop();
      client.subscribe("002/dummy");
      client.loop();
      client.subscribe("002/Node_IR_delete");
      client.loop();
      client.subscribe("002/addIRDevice");
      client.loop();
      client.subscribe("002/wifi_details_rec");
      client.loop();


    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
