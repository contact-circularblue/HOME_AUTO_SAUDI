void send_to_server(String in)
{
  JsonObject& root2 = jsonBuffer.createObject();

  root2["nId"] = String("4234567890");

  String temp0 = in.substring(0, in.indexOf(","));
  Serial.println("temp0=" + temp0);
  String temp1 = in.substring(in.indexOf(",") + 1);
  Serial.println("temp1=" + temp1);
  String temp2 = temp1.substring(0, temp1.indexOf(","));
  Serial.println("temp2=" + temp2);
  String temp3 = temp1.substring(temp1.indexOf(",") + 1);
  Serial.println("temp3=" + temp3);

  if (temp0.toInt() == 0)
  {
    root2["dId"] = temp2;
    if (temp3.toInt() == 1)
      root2["dState"] = String("true");
    else if (temp3.toInt() == 0)
      root2["dState"] = String("false");
    String json2 = "";
    root2.printTo(json2);
    Serial.print("Sending json= "  + json2);
    client.sendJSON("Node_change", json2);
  }

  else if (temp0.toInt() == 1)
  {
    root2["success"] = String("true");
    root2["dId"] = temp2;
    String json2 = "";
    root2.printTo(json2);
    //      Serial.print("Sending json= ");
    //      Serial.println(json);
    client.sendJSON("addIRDevice", json2);
  }
}
