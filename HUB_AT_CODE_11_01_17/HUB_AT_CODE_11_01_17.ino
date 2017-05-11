#include<SoftwareSerial.h>

SoftwareSerial ESP_hub(10, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP_hub.begin(9600);
  //Serial.print("STARTING");
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (ESP_hub.available())
  {
    String input = "";
    while (ESP_hub.available())
    {
      input += char(ESP_hub.read());
      delay(1);
    }
    int index = input.indexOf("hub_says:");
    if (index > -1)
      // if (ESP_hub.find("hub_says:"))
    {
      //      delay(50);
      //      String from_hub = "";
      //      while (ESP_hub.available())
      //      {
      //        from_hub += char(ESP_hub.read());
      //        delay(1);
      //      }
      //      if (from_hub.indexOf("LED") != -1)
      //      {
      //
      //      }
      for (int i = index + 9; i < input.length(); i++)
      {
        Serial.print(input.charAt(i));
      }
    }



    index = input.indexOf("details:");
    if (index > -1)
    {
      for (int i = index + 9; i < input.length(); i++)
      {
        Serial.print(input.charAt(i));
      }
    }
  }



  if (Serial.available())
  {
    delay(50);
    while (Serial.available())
    {
      ESP_hub.print(char(Serial.read()));
      delay(1);
    }
  }
}






