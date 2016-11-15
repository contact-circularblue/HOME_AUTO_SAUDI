void toggle_1()
{
  //Serial.print("I am called");
  flag_1=!flag_1;  
  EEPROM.update(1,flag_1);
  //Serial.println(flag_1);
  if(flag_1 == 1) 
  { 
     digitalWrite(4, HIGH); //write 1 or HIGH to led pin
  } else 
  { 
     digitalWrite(4, LOW);  //write 0 or low to led pin
  }
   delay(500);
}
