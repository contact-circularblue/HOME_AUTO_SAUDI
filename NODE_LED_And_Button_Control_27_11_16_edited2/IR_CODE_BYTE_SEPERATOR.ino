void Code_byte_Seperate(int list_pos)
{
  j=list_pos*50;
  Serial.println("j="+j);
  //j=0;
  /* byte_1=codeValue & a;
    Serial.println(byte_1, HEX);

    byte_code=codeValue & b;
    byte_2=byte_code>>8;
    Serial.println(byte_2, HEX);

    byte_code=codeValue & c;
    byte_3=byte_code>>16;
    Serial.println(byte_3, HEX);
  */
//  int n;
//  if ((codeLen % 8) == 0)
//  {
//    n = codeLen / 8;
//  }
//  else
//  {
//    n = codeLen / 8 + 1;
//  }
  {
//    Serial.print("bytes code will occupy: ");
//    Serial.println(codeLen);

    EEPROM.write(j, codeLen);
//    Serial.print("EEPROM location is ");
//    Serial.println(j);
//    Serial.print("data at location is ");
//    Serial.println(EEPROM.read(j));
    j++;
//    Serial.print("EEPROM location is ");
//    Serial.println(j);
//    Serial.print("codeType stored is ");
//    Serial.println(codeType);
    EEPROM.write(j, codeType);
  int n;
  if ((codeLen % 8) == 0)
  {
    n = codeLen / 8;
  }
  else
  {
    n = codeLen / 8 + 1;
  }
  
    for (int i = 1; i <= n + 1; i++)
    {
      long result = pow(2, (8 * i));
//      Serial.print("result= ");
//      Serial.println(result);
      byte_code = codeValue & result;
      byte_1 = byte_code >> ((8 * i) - 8);
//      Serial.println(byte_1, HEX);

      EEPROM.write(i + j, byte_1);   // j is global
      delay(10);

//      Serial.print("data at EEPROM location ");
//      Serial.print(i + j);
//      Serial.print(" is: ");
//      Serial.println(EEPROM.read(i + j));
    }
  }
  //j = j + 50;
  //  if (j > 150)
  //  {
  //    j = 0;
  //  }

}


