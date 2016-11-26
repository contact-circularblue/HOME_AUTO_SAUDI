void interruptFunction_1()
{
  //interruptCount++;
  flag_1=!flag_1;  
  EEPROM.update(1,flag_1);
  Serial.println(flag_1);
  if(flag_1 == 1) 
  { 
     digitalWrite(4, HIGH); //write 1 or HIGH to led pin
  } else 
  { 
     digitalWrite(4, LOW);  //write 0 or low to led pin
  }
   delay(500);
}

void interruptFunction_2()
{
  interruptCount++;
  flag_2=!flag_2;
  EEPROM.update(2,flag_2);
  Serial.println(flag_2);
  if(flag_2 == 1) 
  {
     digitalWrite(5, HIGH); //write 1 or HIGH to led pin
  } else 
  { 
     digitalWrite(5, LOW);  //write 0 or low to led pin
  }
   delay(500);
}

void interruptFunction_3()
{
  interruptCount++;
  flag_3=!flag_3;
  EEPROM.update(3,flag_3);
  Serial.println(flag_3);
  if(flag_3 == 1) 
  {
     digitalWrite(6, HIGH); //write 1 or HIGH to led pin
  } else
  { 
     digitalWrite(6, LOW);  //write 0 or low to led pin
  }
   delay(500);
}

void interruptFunction_4()
{
  interruptCount++;
  flag_4=!flag_4;
  EEPROM.update(4,flag_4);
  Serial.println(flag_4);
  if(flag_4 == 1) 
  {
     digitalWrite(7, HIGH); //write 1 or HIGH to led pin
  } else 
  { 
     digitalWrite(7, LOW);  //write 0 or low to led pin
  }
   delay(500);
}
