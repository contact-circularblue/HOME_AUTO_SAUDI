// #include <Arduino.h>
//
// void ARD_JSON(String a, char* topic)
// {
//
//
//     StaticJsonBuffer<300> jsonBuffer2;
//
//     Serial.print("json from server =");
//     Serial.println(a);
//
//     JsonObject& root = jsonBuffer2.parseObject(a);
//
//     if (!root.success())
//     {
//       Serial.println("parseObject() failed");
//       return;
//     }
//
//     String success_local = root[String("success")];
//
//     /*CHECK IF THE INCOMING MESSAGE A GENUINE MESSAGE, NOT AN ECHO MESSAGE*/
//     if(success_local=="true")
//     {
//
//     //NODE POWER
//     String topic_local=hub_id+"/"+"Node_power";
//     if(0==strcmp(topic,stringToCharArray(topic_local))) //i.e if the incoming topic is equal to the required topic
//     {
//       node_power(topic);
//     }
//
//     //NODE CHANGE
//     topic_local="";
//     topic_local=hub_id+"/"+"Node_change";
//     if(0==strcmp(topic,stringToCharArray(topic_local)))
//     {
//       JsonObject& root2 = jsonBuffer.createObject();
//       // node_change(topic);
//       root2["nId"] = String("4234567890");
//       String ID=root[String("dId")];
//       root2["dId"] = ID;
//       String state = root[String("dState")];
//       root2["dState"] = state;
//       String json2 = "";
//       root2.printTo(json2);
//       client.publish(topic, stringToCharArray(json2));
//     }
//
//     //WiFi DETAILS
//     topic_local="";
//     topic_local=hub_id+"/"+"wifi_details";
//     if(0==strcmp(topic,stringToCharArray(topic_local)))
//     {
//       wifi_details();
//     }
//
//     //ADD NODE
//     topic_local="";
//     topic_local=hub_id+"/"+"add_Node";
//     if(0==strcmp(topic,stringToCharArray(topic_local)))
//     {
//       add_node(topic);
//     }
//
//     //IR DELETE
//     topic_local="";
//     topic_local=hub_id+"/"+"Node_IR_delete";
//     if(0==strcmp(topic,stringToCharArray(topic_local)))
//     {
//       node_ir_delete(topic);
//     }
//
//     //IR ADD
//     topic_local="";
//     topic_local=hub_id+"/"+"addIRDevice";
//     if(0==strcmp(topic,stringToCharArray(topic_local)))
//     {
//       add_ir_device(topic);
//     }
//
//
//
//   }
// }
// // void getJSON(String in_str, char *out_str)
// // {
// //   int iterator_str = 0;
// //   for (int iterator_s = 0; iterator_s < in_str.length(); iterator_s++) {
// //     if (in_str[iterator_s] != '\\' ) {
// //       out_str[iterator_str] = in_str[iterator_s];
// //       iterator_str++;
// //     }
// //   }
// //   //removes character '\' from in_str and returns a string of characters out_str
// // }
