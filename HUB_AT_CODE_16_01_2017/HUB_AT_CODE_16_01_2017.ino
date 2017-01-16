#include<SoftwareSerial.h>
#include<EEPROM.h>

SoftwareSerial ESP_hub(10, 11);
const byte interruptPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP_hub.begin(9600);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Send_Reset, RISING);  // for sending reset to both ESP's
  //Serial.print("STARTING");
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
    {
      for (int i = index + 9; i < input.length(); i++)
      {
        Serial.print(input.charAt(i));
      }
    }

    index = input.indexOf("details:");
    if (index > -1)
    {
      String ID = "";
      for (int i = index + 8; i < input.indexOf("hub_pass:"); i++)
      {
        ID += input.charAt(i);
      }
      String pass = "";
      for (int i = input.indexOf("hub_pass:") + 9; i < input.indexOf("::::end"); i++)
      {
        pass += input.charAt(i);
      }

      // Save this ID and password to EEPROM
      /*
        location 0=ID length;  from location 1=ID;  location 50=pass length;   from location 51=pass
      */
      EEPROM.write(0, ID.length());
      EEPROM.write(50, pass.length());

      for (int i = 1; i < ID.length() + 1; i++)
      {
        EEPROM.write(i, ID.charAt(i - 1));
      }

      for (int i = 51; i < pass.length() + 51; i++)
      {
        EEPROM.write(i, ID.charAt(i - 51));
      }


      // Send WiFi details to the local network ESP
      Serial.print("details:");
      Serial.print(ID);
      Serial.print(":pass:");
      Serial.print(pass);

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








