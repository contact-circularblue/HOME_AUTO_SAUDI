#include <Arduino.h>
#include <ArduinoJson.h>
#include<SoftwareSerial.h>
#include<EEPROM.h>

#define _SS_MAX_RX_BUFF 128 // Increase software RX buffer size
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

  //node_add.print("node_add");
  //Serial.print("STARTING");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("LOOP STARTED");


  ESP_hub.listen();
  if (ESP_hub.available())
  {
    StaticJsonBuffer<300> Buffer;
    //Serial.println("HUB AVAILABLE");
    String input = "";

    while (ESP_hub.available())
    {
      //Serial.println("IN WHILE");
      input += char(ESP_hub.read());
      delay(5);
    }
    //delay(100);

    //Serial.print("input_string= "+ input);
    JsonObject& from_hub = Buffer.parseObject(input);

    if (!from_hub.success())
    {
      int index = 0;

      //Serial.println("parseObject() failed");

      index = input.indexOf("details:");
      if (index > -1)
      {
        String ID = "";
        for (int i = index + 8; i < input.indexOf(":pass:"); i++)
        {
          ID += input.charAt(i);
        }
        String pass = "";
        for (int i = input.indexOf(":pass:") + 9; i < input.indexOf("::::end"); i++)
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
      //    Serial.print("index=");
      //    Serial.println(input.indexOf("node_add:"));

      index = input.indexOf("node_add:");
      if (index > -1)
      {
        Serial.println("NODE ADDITION");
        node_add.listen();

        String node_ID = "";
        for (int i = 0; i < 10; i++)
        {
          node_add.print("node_add");
          delay(200);
          //                  while(1)
          //                  {
          //                    if(node_add.available())
          //                    Serial.print(char(node_add.read()));
          //                  }
          String temp_str = "";
          if (node_add.available())
          {
            while (node_add.available())
            {
              temp_str += char(node_add.read());
              delay(2);
            }

            Serial.print("temp_str:");
            Serial.println(temp_str);
            if (temp_str.indexOf("ID:") != -1)
            {
              Serial.print("FOUND ID");
              int index = temp_str.indexOf("ID:");
              //while (node_add.available())
              {
                node_ID = temp_str.substring(index + 3);
                //node_ID += char(node_add.read());
                //            ESP_hub.print(char(node_add.read()));
                //delay(50);
              }
              //ESP_hub.print("ID:4234567890");

              int ssid_length = EEPROM.read(0);
              int pass_length = EEPROM.read(50);

              node_add.print("SSID:");
              String send_ssid = "";
              for (int i = 0; i < ssid_length; i++)
                send_ssid += char(EEPROM.read(i + 1));

              node_add.print(send_ssid);

              delay(500);



              int ok_1 = 1;
              for (int i = 0; i < 10; i++)
              {
                if (node_add.find("OK"))
                {
                  Serial.println("GOT OK1");
                  break;
                }
                delay(50);
                if (i == 9)
                  ok_1 = 0;
              }

              if (ok_1 == 1)
              {
                node_add.print("::PASSWORD::");
                String send_pass = "";
                for (int i = 50; i < pass_length + 50; i++)
                {
                  send_pass += char(EEPROM.read(i + 1));
                  delay(1);
                }
                node_add.print(send_pass);
              }

              delay(500);

              String got_OK2 = "";
              while (node_add.available())
                got_OK2 += char(node_add.read());

              Serial.println(got_OK2);

              Serial.println(got_OK2.indexOf("OK"));

              int ok_2 = 1;
              //for (int i = 0; i < 10; i++)
              {
                if (got_OK2.indexOf("OK") != -1)
                {
                  Serial.println("GOT OK2");
                  //break;
                }
                else
                  ok_2 = 0;
              }

              if (ok_2 == 1)
              {
                Serial.print("ID:");
                Serial.println(node_ID);

                
                ESP_hub.print("ID:");
                ESP_hub.print(node_ID);
                break;
              }

            }

          }
          delay(1000);
        }
        //Serial.println("LISTENING TO HUB");
        ESP_hub.listen();
      }
      //return;
    }

    else
    {
      String success = from_hub[String("s")];
      if (success == "t")
        Serial.print(input);
    }

    // int index = input.indexOf("hub_says:");
    // if (index > -1)
    // {
    //
    // }


  }


  if (Serial.available())
  {
    String data_from_UDP = "";

    while (Serial.available())
    {
      data_from_UDP += char(Serial.read());
      delay(2);
    }

    //    ESP_hub.println("data_from_UDP:");
    //    ESP_hub.println(data_from_UDP);


    //delay(50);
    //    while (Serial.available())
    //    {
    //      ESP_hub.print(char(Serial.read()));
    //      delay(1);
    //    }
    StaticJsonBuffer<300> Buffer;
    JsonObject& from_UDP = Buffer.parseObject(data_from_UDP);
    
    if(data_from_UDP.indexOf("WIFI_ACK")!=-1)
    {
      ESP_hub.print("WIFI_ACK");
    }

    else if (!from_UDP.success())
    {
      //      ESP_hub.println("parseObject() failed");
    }
    else
    {
      //Serial.println("
      ESP_hub.print(data_from_UDP);
    }
    
  }
}
