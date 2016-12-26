void actuate(char action_local, int switch_num, int switch_value)
{
  if (action_local == '0')
  {
    //en_int();  ///////////////////////////////re enable the interrupts when the ir addition is complete

    if (switch_num > 0 && switch_num <= 4)
    {
      //Serial.println("toggle LED");
      toggle_LED();
    }
    else if (switch_num > 4 && switch_num <= 30)
    {
      Serial.println("IR");
      Serial.println("Pressed, sending");
      sendCode(switch_num);
      delay(50);
      while (digitalRead(BUTTON_PIN) == HIGH);
      //irrecv.enableIRIn();
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
      while (!irrecv.decode(&results));
      {
        //Serial.println("Recvd code");
        decode_results *got_results = &results;
        //if (got_results->decode_type >= -1)   // will work for all type of codes
        if (got_results->decode_type == -1)      // will wok only for unknown codes
        {
          if (got_results->bits > 0 || got_results->rawlen > 7)
          {
            //            Serial.println("GOT RC6");
            //            Serial.print("GOT length= ");
            //            Serial.println(got_results->bits);
            //            Serial.print("type=");
            //            Serial.println(got_results->decode_type);
            break;
          }
        }
        //irrecv.resume();
      }
    }

    if (listSize < 13)
    {
      listSize++;
      EEPROM.write(985, listSize);
      //      Serial.print("listSize=");
      //      Serial.println(listSize);
      storeCode(&results, listSize - 1);

      String max_dev = "";
      max_dev += max_devices;
      int IR_dev_ID = listSize + max_dev.toInt();

      String Str_IR_dev_ID = String(IR_dev_ID);

      String Send_to_ESP = "1,";
      Send_to_ESP += Str_IR_dev_ID; 
      Send_to_ESP += ",";
      Send_to_ESP += "0";
      Serial.print(Send_to_ESP);

while(Serial.available())
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


