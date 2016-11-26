void Code_byte_Seperate()
{
  byte_1=codeValue & a;
  Serial.println(byte_1, HEX);
  
  byte_code=codeValue & b;
  byte_2=byte_code>>8;
  Serial.println(byte_2, HEX);

  byte_code=codeValue & c;
  byte_3=byte_code>>16;
  Serial.println(byte_3, HEX);

  
}

