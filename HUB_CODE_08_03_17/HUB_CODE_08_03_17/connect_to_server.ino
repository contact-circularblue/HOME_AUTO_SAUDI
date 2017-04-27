#include <Arduino.h>

bool connect_to_server()
{
  while (!client.connect(host, port))
    {   
      Serial.println("connection failed");
      delay(2000);
    }
    return true;
}
