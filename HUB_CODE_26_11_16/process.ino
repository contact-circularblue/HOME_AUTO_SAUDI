void process()
{
  
  if (RID != "")
  {
    if (RID == "wifi_details")
    {
      Serial.print("RID= ");
      Serial.println(RID);
      
//      Serial.print("Rname= ");
//      Serial.println(Rname);
//
//      Serial.print("Rcontent= ");
//      Serial.println(Rcontent);
      
      ARD_JSON(Rcontent);
      data0_val.toCharArray(ssid, data0_val.length() + 1);
      data1_val.toCharArray(password, data1_val.length() + 1);

Serial.print("WiFi details received=SSID:");//+" PASSWORD:"+password);
Serial.print(data0_val);

for(int i=0;i<=data0_val.length();i++)
ssid[i]=data0_val[i];

Serial.print("||password:");//+" PASSWORD:"+password);
Serial.println(password);

for(int i=0;i<=data1_val.length();i++)
password[i]=data1_val[i];

      while (!connect_wifi(ssid, password));
      //while (!connect_to_server());
      if(WiFi.status() == WL_CONNECTED)
      {
      Serial.println("wifi connected");

      delay(100);
      //monitor_client();/// The server has returned message="connected". Just read it out of the buffer.

      //add_hub();

      delay(100);
//      Serial.print("Sending ACK\n");
      client.send("wifi_details_rec", "message", "success");
      
      delay(100);
      
      }
    }
    else if (RID == "add_Node")
    {
//      Serial.println("Adding Node");
      delay(10);
      String node_Id = "4234567890";

      JsonObject& root = jsonBuffer.createObject();
      root["nodeId"] = node_Id;
      root["type"] = String(node_Id[0]);
      String json = "";
      root.printTo(json);
//      Serial.print("Sending json= ");
//      Serial.println(json);
      client.sendJSON("add_Node", json);
      
      
      delay(3000);
      
      

  


    }
    
//    else if (RID == "dummy")
//    {
//      Serial.println("Dummy reply ID= " +RID);
//    }
    
    else if(RID == "Node_change")
    {
//      Serial.println("Node_change requested");
//      Serial.println("nodeId= " +nodeId +"deviceId=" +deviceId +"deviceState=" +deviceState);

      JsonObject& root = jsonBuffer.createObject();
      
      root["nId"] = String(nodeId);
      root["dId"] = String(deviceId);
      root["dState"] = String(deviceState);
      String json = "";
      root.printTo(json);
//      Serial.print("Sending json= ");
//      Serial.println(json);
      client.sendJSON("Node_change", json);
      
      Serial.println();
      Serial.print("hub_says:");
      Serial.print("jackhammer,"); ////NODE ID for example
      Serial.print("0"); //// NODE CHANGE FOR SWITCHES
      Serial.print(",");
      Serial.print(deviceId);
      Serial.print(",");
      if(deviceState=="true")
      Serial.print("1");
      else if(deviceState=="false")
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
    
    else if(RID == "addIRDevice")
    {
      Serial.println("RID= addIRDevice");
      Serial.println("success="+data0_val);
      Serial.println("nId="+data1_val);
      
      delay(3000);
      
      JsonObject& root = jsonBuffer.createObject();
      
      
      String deviceId="5";
      
      root["success"] = String(data0_val);
      root["nId"] = String(data1_val);
      root["dId"] = String(deviceId);
      String json = "";
      root.printTo(json);
      Serial.print("Sending json= ");
      Serial.println(json);
      client.sendJSON("addIRDevice", json);
    }
    
    else
    {
      Serial.println("RID NOT FOUND");
    }
  }
}
