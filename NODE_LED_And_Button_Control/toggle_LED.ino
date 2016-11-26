void  toggle_LED()
{
  //Serial.print("I am called");
  if(node_switch=='1')
  {
   if(state=='1')
    {
     flag_1=1;  
     EEPROM.update(1,flag_1);
     digitalWrite(4, HIGH); //write 1 or HIGH to led pin
     //////////////////Serial.print("HIGH");
    }
   else if(state=='0')
    { 
     flag_1=0;  
     EEPROM.update(1,flag_1);
     digitalWrite(4, LOW); //write 1 or HIGH to led pin
     //////////////////Serial.print("LOW");
    }  
  }  
  
  else if(node_switch=='2')
  {
   if(state=='1')
    {
     flag_2=1;  
     EEPROM.update(2,flag_2);
     digitalWrite(5, HIGH); //write 1 or HIGH to led pin
     //////////////////Serial.print("HIGH");
    }
   else if(state=='0')
    { 
     flag_2=0;  
     EEPROM.update(2,flag_2);
     digitalWrite(5, LOW); //write 1 or HIGH to led pin
     //////////////////Serial.print("LOW");
    } 
  }

  else if(node_switch=='3')
  {
   if(state=='1')
    {
     flag_3=1;  
     EEPROM.update(3,flag_3);
     digitalWrite(6, HIGH); //write 1 or HIGH to led pin
     //////////////////Serial.print("HIGH");
    }
   else if(state=='0')
    { 
     flag_3=0;  
     EEPROM.update(3,flag_3);
     digitalWrite(6, LOW); //write 1 or HIGH to led pin
     //////////////////Serial.print("LOW");
    } 
  }

   else if(node_switch=='4')
  {
   if(state=='1')
    {
     flag_4=1;  
     EEPROM.update(4,flag_4);
     digitalWrite(7, HIGH); //write 1 or HIGH to led pin
     //////////////////Serial.print("HIGH");
    }
   else if(state=='0')
    { 
     flag_4=0;  
     EEPROM.update(4,flag_4);
     digitalWrite(7, LOW); //write 1 or HIGH to led pin
     //////////////////Serial.print("LOW");
    } 
  }

//  delay(500);
}
