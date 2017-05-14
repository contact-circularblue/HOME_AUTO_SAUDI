void interruptFunction_1()
{
  disable_interrupts();
  //interruptCount++;
  flag_1 = !EEPROM.read(1001);
  EEPROM.update(1001, flag_1);
  //  Serial.println(flag_1);
  if (flag_1 == 1)
  {
    digitalWrite(4, HIGH); //write 1 or HIGH to led pin
  } else
  {
    digitalWrite(4, LOW);  //write 0 or low to led pin
  }

//  Serial.println("START");
//  Serial.println("DONE");


  Send_to_ESP = "0,";
  Send_to_ESP += "1,";
  Send_to_ESP += char(flag_1 + 48);
  Serial.print(Send_to_ESP);


  Timer1.initialize(50000);
  while (1)
  {
    unsigned long time = Timer1.read();
    if (time >= 40000)
      break;
  }
  Timer1.initialize(50000);
  while (1)
  {
    unsigned long time = Timer1.read();
    if (time >= 40000)
      break;
  }
  en_int();
}

void interruptFunction_2()
{
  disable_interrupts();
  interruptCount++;
  flag_2 = !EEPROM.read(1002);
  EEPROM.update(1002, flag_2);
  //  Serial.println(flag_2);
  if (flag_2 == 1)
  {
    digitalWrite(5, HIGH); //write 1 or HIGH to led pin
  } else
  {
    digitalWrite(5, LOW);  //write 0 or low to led pin
  }
  delay(50);

  Send_to_ESP = "0,";
  Send_to_ESP += "2,";
  Send_to_ESP += char(flag_2 + 48);
  Serial.print(Send_to_ESP);
  delay(1000);
  en_int();
}

void interruptFunction_3()
{
  disable_interrupts();
  interruptCount++;
  flag_3 = !EEPROM.read(1003);
  EEPROM.update(1003, flag_3);
  //  Serial.println(flag_3);
  if (flag_3 == 1)
  {
    digitalWrite(6, HIGH); //write 1 or HIGH to led pin
  } else
  {
    digitalWrite(6, LOW);  //write 0 or low to led pin
  }
  delay(50);

  Send_to_ESP = "0,";
  Send_to_ESP += "3,";
  Send_to_ESP += char(flag_3 + 48);
  Serial.print(Send_to_ESP);
  delay(1000);
  en_int();
}

void interruptFunction_4()
{
  disable_interrupts();
  interruptCount++;
  flag_4 = !EEPROM.read(1004);
  EEPROM.update(1004, flag_4);
  //  Serial.println(flag_4);
  if (flag_4 == 1)
  {
    digitalWrite(7, HIGH); //write 1 or HIGH to led pin
  } else
  {
    digitalWrite(7, LOW);  //write 0 or low to led pin
  }
  delay(50);

  Send_to_ESP = "0,";
  Send_to_ESP += "4,";
  Send_to_ESP += char(flag_4 + 48);
  Serial.print(Send_to_ESP);
  delay(1000);
  en_int();
}

