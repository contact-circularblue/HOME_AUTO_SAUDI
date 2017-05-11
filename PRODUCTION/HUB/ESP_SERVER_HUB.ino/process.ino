#include <Arduino.h>

void process(char* rec_topic, byte* payload_local, int len)
{
  // Serial.println(rec_topic);
  String json_in="";
  for (int i = 0; i < len; i++) {
    // Serial.print((char)payload_local[i]);
    json_in+=(char)payload_local[i];
  }
  //
  // Serial.println();
  ARD_JSON(json_in, rec_topic);

  // while(1)
  // {
  //   delay(1);
  // }
}
