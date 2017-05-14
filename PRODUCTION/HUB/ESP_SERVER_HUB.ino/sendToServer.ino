#include <Arduino.h>

void send_to_server(String in)
{
//  Serial.print("in:");
//  Serial.println(in);

  StaticJsonBuffer<300> jsonBuffer;

  JsonObject& root2 = jsonBuffer.createObject();

  StaticJsonBuffer<300> jsonBuffer_in;

  JsonObject& from_nodes = jsonBuffer_in.parseObject(in);

  String success = from_nodes[String("s")];



  if (from_nodes.success())
  {
    if (success == "t")// && from_hub[String("nId")] == Node_Name)
    {
      String nId = from_nodes[String("nId")];
      String dId = from_nodes[String("dId")];
      String ACK = from_nodes[String("ACK")];
      String REQ = from_nodes[String("REQ")];
      String VAL = from_nodes[String("VAL")];

      if (ACK == "T")
      {
        if (REQ == "0")
        {
          if (dId.toInt() <= 16)
          {
            root2["nId"] = nId;
            root2["dId"] = dId;
            if (VAL.toInt() == 1)
              root2["dState"] = String("true");
            else if (VAL.toInt() == 0)
              root2["dState"] = String("false");


            String json2 = "";
            root2.printTo(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "Node_change";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }
        }
      }
      else if (ACK == "F")
      {
        if (REQ == "0")
        {
          if (dId.toInt() <= 5)
          {
            root2["nId"] = nId;
            root2["dId"] = dId;
            if (VAL.toInt() == 1)
              root2["dState"] = String("true");
            else if (VAL.toInt() == 0)
              root2["dState"] = String("false");


            String json2 = "";
            root2.printTo(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "Node_change";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }
        }

//        Serial.print("REQ=");
//        Serial.println(REQ);
//
//        Serial.print("dId=");
//        Serial.println(dId);

        if (REQ == "0")
        {
          if (dId.toInt() <= 5)
          {
            root2["nId"] = nId;
            root2["dId"] = dId;
            if (VAL.toInt() == 1)
              root2["dState"] = String("true");
            else if (VAL.toInt() == 0)
              root2["dState"] = String("false");


            String json2 = "";
            root2.printTo(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "Node_change";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }

          if (dId.toInt() == 30)
          {
            root2["nId"] = nId;
            root2["power"] = VAL;
            //            if (VAL.toInt() == 1)
            //              root2["dState"] = String("true");
            //            else if (VAL.toInt() == 0)
            //              root2["dState"] = String("false");


            String json2 = "";
            root2.printTo(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "Node_power";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }
        }

        if (REQ == "1")
        {
//          Serial.println("REQ=1");
//
//          Serial.print("dId=");
//          Serial.println(dId);

          if (dId.toInt() != 30)
          {
            root2["nId"] = nId;
            root2["s"] = String("t");
            root2["dId"] = dId;

            String json2 = "";
            root2.printTo(json2);

//            Serial.print("IR JSON=");
//            Serial.print(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "addIRDevice";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }

          else if (dId.toInt() == 30)
          {
            root2["nId"] = nId;
            root2["s"] = String("f");
            root2["dId"] = dId;

            String json2 = "";
            root2.printTo(json2);

            String topic_local = "";
            topic_local = hub_id + "/" + "addIRDevice";

            char tem1[50];
            char tem2[50];

            client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
          }
        }

      }
    }
  }





  //  root2["nId"] = String("4234567890");
  //
  //
  //  String temp0 = in.substring(0, in.indexOf(","));
  //  Serial.println("temp0=" + temp0);
  //  String temp1 = in.substring(in.indexOf(",") + 1);
  //  Serial.println("temp1=" + temp1);
  //  String temp2 = temp1.substring(0, temp1.indexOf(","));
  //  Serial.println("temp2=" + temp2);
  //  String temp3 = temp1.substring(temp1.indexOf(",") + 1);
  //  Serial.println("temp3=" + temp3);
  //  String temp4 = temp3.substring(0, temp3.indexOf("\\"));
  //  Serial.println("temp4=" + temp4);
  //
  //  if (temp0.toInt() == 0)
  //  {
  //    if (temp2.toInt() <= 5) // for 6 switch node
  //    {
  //      root2["dId"] = temp2;
  //      if (temp3.toInt() == 1)
  //        root2["dState"] = String("true");
  //      else if (temp3.toInt() == 0)
  //        root2["dState"] = String("false");
  //
  //
  //      String json2 = "";
  //      root2.printTo(json2);
  //      //    Serial.print("Sending json= "  + json2);
  //      String topic_local = "";
  //      topic_local = hub_id + "/" + "Node_change";
  //
  //      char tem1[50];
  //      char tem2[50];
  //
  //      client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
  //    }
  //    else if (temp2.toInt() == 30)
  //    {
  //      root2["power"] = String(temp4);
  //      String json2 = "";
  //      root2.printTo(json2);
  //
  //      String topic_local = "";
  //      topic_local = hub_id + "/" + "Node_power";
  //
  //      char tem1[50];
  //      char tem2[50];
  //
  //      client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
  //
  //      Serial.println();
  //      Serial.print("json2= " + json2);
  //    }
  //    Serial.print("json sent");
  //  }
  //
  //  else if (temp0.toInt() == 1)
  //  {
  //    if (temp2 != "30")
  //    {
  //      String topic_local = "";
  //      topic_local = hub_id + "/" + "addIRDevice";
  //
  //
  //      root2["s"] = String("t");
  //      root2["dId"] = temp2;
  //      String json2 = "";
  //      root2.printTo(json2);
  //
  //      char tem1[50];
  //      char tem2[50];
  //
  //      client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
  //    }
  //    else
  //    {
  //      String topic_local = "";
  //      topic_local = hub_id + "/" + "addIRDevice";
  //
  //
  //      root2["s"] = String("f");
  //      root2["dId"] = temp2;
  //      String json2 = "";
  //      root2.printTo(json2);
  //
  //      char tem1[50];
  //      char tem2[50];
  //
  //      client.publish(stringToCharArray(topic_local, tem1), stringToCharArray(json2, tem2));
  //    }
  //
  //  }
}
