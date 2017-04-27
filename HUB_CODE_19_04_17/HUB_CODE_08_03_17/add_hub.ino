#include <Arduino.h>

void add_hub()
{
  hub_connected = false;
  while (!hub_connected)
  {
    //    Serial.print("Sending JSON");
    //    JsonObject& root2 = jsonBuffer.createObject();
    //    struct DeviceType_ {
    //      String Hub = "Hub";
    //    } DeviceType;
    //
    //    root2["deviceType"] = DeviceType.Hub;
    //    root2["uniqueID"] = "1234";
    //
    //    String json = "";
    ////    Serial.print("printing to string");
    //    root2.printTo(json);

    //Serial.print("Sending JSON NOW");

    client.sendJSON("addDevice", json_add_hub);

    delay(100);

    Serial.print("JSON sent");

    while (!monitor_client())
    {
      delay(1);
    }
    if (RID == "ack" && success_val == "true");
    {
      hub_connected = true;
    }

  }
}
