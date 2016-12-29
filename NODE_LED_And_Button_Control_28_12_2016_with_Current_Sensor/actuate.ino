void actuate(char action_local, int switch_num, int switch_value)
{
  if (action_local == '0')
  {
    if (switch_num > 0 && switch_num <= 4)
    {
      //Serial.println("toggle LED");
      toggle_LED();
    }
    else if (switch_num > 4 && switch_num <= 29)
    {
      Serial.println("IR");
      Serial.println("Pressed, sending");
      sendCode(switch_num);
      delay(50);
      while (digitalRead(BUTTON_PIN) == HIGH);
      //irrecv.enableIRIn();
    }
    else if (switch_num == 30)
    {
      float power = measure_current();
      Serial.print("0,30,");
      Serial.print(power);
    }
  }
  if (action_local == '1')
  {
    disable_interrupts();  /////////////////////disable the switches at the time of IR addition

    //Serial.println("initializing IR Add");
    int got_code = 0;
    irrecv.enableIRIn();
    while (1)
    {
      previousMillis = millis();
      while (!irrecv.decode(&results))
      {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
          previousMillis = currentMillis;
          while (Serial.available())
          {
            Serial.read();
          }
          Serial.println("Breaking");
          en_int();  ///////////////////////////////re enable the interrupts when the ir addition is complete
          break;
        }
      }

      //Serial.println("Recvd code");
      decode_results *got_results = &results;
      if (got_results->decode_type >= -1)   // will work for all type of codes
        // if (got_results->decode_type == -1)      // will wok only for unknown codes
      {
        if (got_results->bits > 0 || got_results->rawlen > 7)
        {
          ListSize=EEPROM.read(985); 
          if (EEPROM.read(985) < 13)
          {
            int List_Size = IR_ADD();
            //            listSize++;
            //            EEPROM.write(985, listSize);

            storeCode(&results, List_Size - 1);

//            Serial.print(" List_Size =");
//            Serial.println(List_Size);

            String max_dev = "";
            max_dev += max_devices;
            int IR_dev_ID = List_Size + max_dev.toInt();

            Serial.print(" IR_dev_ID =");
            Serial.println(IR_dev_ID);


            String Str_IR_dev_ID = String(IR_dev_ID);

            String Send_to_ESP = "1,";
            Send_to_ESP += Str_IR_dev_ID;
            Send_to_ESP += ",";
            Send_to_ESP += "0";
            Serial.print(Send_to_ESP);

            while (Serial.available())
            {
              Serial.read();
            }
            irrecv.resume();

            en_int();  ///////////////////////////////re enable the interrupts when the ir addition is complete
          }

          else
          {
            Serial.println("List Full");
            en_int();  ///////////////////////////////re enable the interrupts when the ir addition is complete
          }
        }
      }

      break;
    }
  }

  else if (action_local == '2')
  {
    //    IR_DELETE(int IR_NUM);
    Serial.print("deletion");
  }

}


