#include<SoftwareSerial.h>
#include<EEPROM.h>

SoftwareSerial ESP_hub(10, 11);
SoftwareSerial node_add(8, 9);
const byte interruptPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP_hub.begin(9600);
  node_add.begin(9600);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Send_Reset, RISING);  // for sending reset to both ESP's
  //Serial.print("STARTING");
}

void loop() {
  // put your main code here, to run repeatedly:
  ESP_hub.listen();
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
        EEPROM.write(i, pass.charAt(i - 51));
      }


      // Send WiFi details to the local network ESP
      Serial.print("details:");
      Serial.print(ID);
      Serial.print(":pass:");
      Serial.print(pass);

    }

    index = input.indexOf("node_add:");
    if (index > -1)
    {
      Serial.println("NODE ADDITON");
      node_add.listen();

      String node_ID = "";
      for (int i = 0; i < 30; i++)
      {
        node_add.print("node_add");
        delay(200);
        //        while(1)
        //        {
        //          if(node_add.available())
        //          ESP_hub.print(char(node_add.read()));
        //        }
        String temp_str = "";
        if (node_add.available())
        {
          while (node_add.available())
          {
            temp_str += char(node_add.read());
            delay(10);
          }
          if (temp_str.indexOf("ID:") != -1)
          {
            //ESP_hub.print("FOUND ID");
            int index = temp_str.indexOf("ID:");
            //while (node_add.available())
            {
              node_ID = temp_str.substring(index+3);
              //node_ID += char(node_add.read());
              //            ESP_hub.print(char(node_add.read()));
              //delay(50);
            }
            //ESP_hub.print("ID:4234567890");

            int ssid_length = EEPROM.read(0);
            int pass_length = EEPROM.read(50);

            node_add.print("SSID:");
            for (int i = 0; i < ssid_length; i++)
              node_add.print(char(EEPROM.read(i + 1)));

            int ok_1 = 1;
            for (int i = 0; i < 10; i++)
            {
              if (node_add.find("OK"))
                break;
              delay(50);
              if (i == 9)
                ok_1 = 0;
            }

            if (ok_1 == 1)
            {
              node_add.print("::PASSWORD::");
              for (int i = 50; i < pass_length + 50; i++)
                node_add.print(char(EEPROM.read(i + 1)));
            }

            int ok_2 = 1;
            for (int i = 0; i < 10; i++)
            {
              if (node_add.find("OK"))
                break;
              delay(50);
              if (i == 9)
                ok_2 = 0;
            }

            if (ok_2 == 1)
            {
              ESP_hub.print("ID:");
              ESP_hub.print(node_ID);
              break;
            }

          }
         
        }
         delay(1000);
      }
      ESP_hub.listen();
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








