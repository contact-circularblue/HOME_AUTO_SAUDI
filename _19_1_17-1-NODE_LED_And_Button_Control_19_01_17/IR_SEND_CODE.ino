void sendCode(int num)
{
  int m = (num - 5) * 80;

  unsigned int combine_byte[78];
  int bytes = EEPROM.read(m);
  codeLen = bytes;

  if (EEPROM.read(m + 1) != 255)
  {

    if ((codeLen % 8) == 0)
    {
      bytes = codeLen / 8;
    }
    else
    {
      bytes = codeLen / 8 + 1;
    }
  }
  //        Serial.print("bytes=");
  //        Serial.println(bytes);

  // m++;

  codeType = EEPROM.read(m + 1);
  if (codeType == 255)
  {
    codeType = -1;
  }

  //codeType=RC6;
  Serial.print("codeType=");
  Serial.println(codeType);

  m++;
  m++;

  for (int i = 0; i < bytes; i++)
  {
    //    Serial.print("location read=");
    //    Serial.println(m + i);
    //    Serial.print("value read=");
    //    Serial.println(EEPROM.read(m + i), HEX);
    combine_byte[i] = EEPROM.read(m + i);
  }

  //  Serial.println("the array is :");
  //  for (int i = 0; i < bytes; i++)
  //  {
  //    Serial.print(EEPROM.read(m + i), HEX);
  //    Serial.println();
  //  }
  if (codeType != -1)
  {
    codeValue = combine(bytes, combine_byte);
    Serial.print("combined string=");
    Serial.println(codeValue, HEX);
  }
  // codeValue=p;
  // codeLen=EEPROM.read(m);

  // codeValue=codeValue+1;
  //codeLen=20;

  // codeType = RC6;

  //  Serial.print("codeLen=");
  //  Serial.println(codeLen);

  if (codeType == NEC)
  {
    //    if (repeat) {
    //      irsend.sendNEC(REPEAT, codeLen);
    //      Serial.println("Sent NEC repeat");
    //    }
    //    else {
    irsend.sendNEC(codeValue, codeLen);
    Serial.print("Sent NEC ");
    Serial.println(codeValue, HEX);
    //    }
  }

  else if (codeType == SONY)
  {
    irsend.sendSony(codeValue, codeLen);
    Serial.print("Sent Sony ");
    Serial.println(codeValue, HEX);
  }

  else if (codeType == RC5 || codeType == RC6)
  {
    Serial.print("codeLen= ");
    Serial.println(codeLen);

    if (codeType == RC5)
    {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue, HEX);
      irsend.sendRC5(codeValue, codeLen);
    }
    else
    {
      irsend.sendRC6(codeValue, codeLen);
      Serial.print("Sent RC6 ");
      Serial.println(codeValue, HEX);
    }
  }

  else if (codeType == UNKNOWN /* i.e. raw */)
  {
    // Assume 38 KHz

    for (int i = 1; i < bytes+1; i++)
    {
       if (i % 2) {
        // Mark
        rawCodes[i-1] = combine_byte[i-1] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i-1] = combine_byte[i-1] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      
      //rawCodes[i]=combine_byte[i];
    }

    irsend.sendRaw(rawCodes, codeLen, 38);
    Serial.println("Sent raw");
  }
}
