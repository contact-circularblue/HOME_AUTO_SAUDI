void ARD_JSON(String a)
{
  StaticJsonBuffer<300> jsonBuffer;
  char json[a.length()];
  getJSON(a, json);

//  Serial.print("json string=");
//  Serial.println(json);

  JsonObject& root = jsonBuffer.parseObject(json);
  String success_local = root[String("success")];

  success_val = success_local;
//  Serial.print("success= ");
//  Serial.print(success_val);
//  Serial.print("\t");

  String message_local = root[String("message")];
  message_val = message_local;
//  Serial.print("message= ");
//  Serial.print(message_val);
//  Serial.print("\t");

  String data0 = root["message"][0];
  data0_val = data0;

  String data1 = root["message"][1];
  data1_val = data1;

  if (RID == "Node_change")
  {
    String nodeId_local = root[String("nId")];
    String deviceId_local = root[String("dId")];
    String deviceState_local = root[String("dState")];

    nodeId = nodeId_local;
    deviceId = deviceId_local;
    deviceState = deviceState_local;

  }

  if (RID == "addIRDevice")
  {
   String data0 = root[String("success")];
  data0_val = data0;

  String data1 = root[String("nId")];
  data1_val = data1; 
  }



//  Serial.print("data0_val= ");
//  Serial.print(data0_val);
//  Serial.print("\t");
//
//  Serial.print("data1_val= ");
//  Serial.print(data1_val);
//  Serial.print("\t");
//  Serial.println();
}
void getJSON(String in_str, char *out_str)
{
  int iterator_str = 0;
  for (int iterator_s = 0; iterator_s < in_str.length(); iterator_s++) {
    if (in_str[iterator_s] != '\\' ) {
      out_str[iterator_str] = in_str[iterator_s];
      iterator_str++;
    }
  }
  //removes character '\' from in_str and returns a string of characters out_str
}

