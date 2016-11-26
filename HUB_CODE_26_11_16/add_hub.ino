void add_hub()
{
  hub_connected = false;
  while (!hub_connected)
  {
    //    Serial.println("Sending device type");
    //    client.send("DeviceType", "message", "Hub"); // Tell the server that what has connected to it now is a HUB type device
    //    /// Nothing is returned form the server after this command
    //    delay(100);
    //    Serial.println("Sending new device ID");
    //    client.send("new user", "message", "1234");
    //
    //    delay(100);
    //
    //    if (monitor_client())
    //    {
    //      hub_connected = true;
    //    }
    JsonObject& root = jsonBuffer.createObject();
    struct DeviceType_{
      String Hub = "Hub";
    }DeviceType;
    
    root["deviceType"] = DeviceType.Hub;
    root["uniqueID"] = "1234";
    
    String json = "";
    root.printTo(json);

    client.sendJSON("addDevice", json);
    
    delay(100);

    while (!monitor_client());
//    Serial.print("state=");
//    Serial.println(state);
    if(RID=="ack" && success_val=="true");
    {
//      Serial.print("monitor_client returned TRUE");
      hub_connected = true;
    }
//    Serial.print("hub_connected=");
//    Serial.println(hub_connected);
  }
}
