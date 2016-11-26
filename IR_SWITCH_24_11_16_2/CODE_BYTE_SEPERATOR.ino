void Code_byte_Seperate()
{
  /* byte_1=codeValue & a;
    Serial.println(byte_1, HEX);

    byte_code=codeValue & b;
    byte_2=byte_code>>8;
    Serial.println(byte_2, HEX);

    byte_code=codeValue & c;
    byte_3=byte_code>>16;
    Serial.println(byte_3, HEX);
  */
  int n;
  if ((codeLen % 8) == 0)
  {
    n = codeLen / 8;
  }
  else
  {
    n = codeLen / 8 + 1;
  }
  Serial.print("bytes code will occupy: ");
  Serial.println(n);

  for (int i = 1; i <= n; i++)
  {
    long result = pow(2, (8 * i));
    Serial.print("result= ");
    Serial.println(result);
    byte_code = codeValue & result;
    byte_1 = byte_code >> ((8 * i) - 8);
    Serial.println(byte_1, HEX);
  }
}

