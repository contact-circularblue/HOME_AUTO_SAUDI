bool connect_socket()
{
  while (socket_connected != true)
    client.monitor();
//    Serial.print("RID=");
//    Serial.println(RID);
//    Serial.print("FUll received message=");
//    Serial.println(rcvd_msg_full);
    
  return true;
}
