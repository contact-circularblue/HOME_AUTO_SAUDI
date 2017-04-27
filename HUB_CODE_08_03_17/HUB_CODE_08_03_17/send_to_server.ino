#include <Arduino.h>

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
  String temp4 = temp3.substring(0, temp3.indexOf("\\"));
  Serial.println("temp4=" + temp4);

  if (temp0.toInt() == 0)
  {
    if (temp2.toInt() <= 5) // for 6 switch node
    {
      root2["dId"] = temp2;
      if (temp3.toInt() == 1)
        root2["dState"] = String("true");
      else if (temp3.toInt() == 0)
        root2["dState"] = String("false");


      String json2 = "";
      root2.printTo(json2);
      //    Serial.print("Sending json= "  + json2);

      client.sendJSON("Node_change", json2);
    }
    else if (temp2.toInt() == 30)
    {
      root2["power"] = String(temp4);
      String json2 = "";
      root2.printTo(json2);
      client.sendJSON("Node_power", json2);
      Serial.println();
      Serial.print("json2= " + json2);
    }
    Serial.print("json sent");
  }

  else if (temp0.toInt() == 1)
  {
    if(temp2!="30")
    {
    root2["success"] = String("true");
    root2["dId"] = temp2;
    String json2 = "";
    root2.printTo(json2);
    //      Serial.print("Sending json= ");
    //      Serial.println(json);
    client.sendJSON("addIRDevice", json2);
    }
    else
    {
      root2["success"] = String("false");
    root2["message"] = "List Full";
    String json2 = "";
    root2.printTo(json2);
    //      Serial.print("Sending json= ");
    //      Serial.println(json);
    client.sendJSON("addIRDevice", json2);
    }
    
  }
}
