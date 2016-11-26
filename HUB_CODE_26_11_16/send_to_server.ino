void send_to_server(String in)
{
      JsonObject& root2 = jsonBuffer.createObject();
      
      root2["nId"] = String("4234567890");
      root2["dId"] = String(in.charAt(2));
      if(in.charAt(4)=='1')
      root2["dState"] = String("true");
      else if(in.charAt(4)=='0')
      root2["dState"] = String("false");
      String json2 = "";
      root2.printTo(json2);
      Serial.print("Sending json= "  + json2);
      client.sendJSON("Node_change", json2);
}
