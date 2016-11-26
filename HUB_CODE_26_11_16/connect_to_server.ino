bool connect_to_server()
{
  while (!client.connect(host, port))
    {   
      Serial.println("connection failed");
      delay(1000);
    }
    return true;
}
