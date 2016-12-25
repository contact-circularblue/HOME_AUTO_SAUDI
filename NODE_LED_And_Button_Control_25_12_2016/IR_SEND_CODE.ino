void sendCode(int num) {

  int m = (num-5)*80;

  int combine_byte[45];
  int bytes = EEPROM.read(m);
  codeLen = bytes;


  if ((codeLen % 8) == 0)
  {
    bytes = codeLen / 8;
  }
  else
  {
    bytes = codeLen / 8 + 1;
  }
  //        Serial.print("bytes=");
  //        Serial.println(bytes);


  m++;

  codeType = EEPROM.read(m);
//  Serial.print("codeType=");
//  Serial.println(codeType);

  m++;

if(codeType!= UNKNOWN)
{
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

  codeValue = combine(bytes, combine_byte);
//  Serial.print("combined string=");
//  Serial.println(codeValue, HEX);
  // codeValue=p;
  // codeLen=EEPROM.read(m);

  // codeValue=codeValue+1;
  //codeLen=20;
//  codeType = RC6;   //////////////////////////////////////////////////
//  Serial.print("codeLen=");
//  Serial.println(codeLen);

  if (codeType == NEC) {

  }
  else if (codeType == SONY) {
    irsend.sendSony(codeValue, codeLen);
    Serial.print("Sent Sony ");
    Serial.println(codeValue, HEX);
  }
  else if (codeType == RC5 || codeType == RC6) {
    //    if (!repeat) {
    //      // Flip the toggle bit for a new button press
    //      toggle = 1 - toggle;
    //    }
    // Put the toggle bit into the code to send
    //Serial.print("Sent RC5 ");
    Serial.print("codeLen= ");
    Serial.println(codeLen);
    //    codeValue = codeValue & ~(1 << (codeLen - 1));
    //    codeValue = codeValue | (toggle << (codeLen - 1));


    if (codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue, HEX);
      irsend.sendRC5(codeValue, codeLen);
    }
    else {
      irsend.sendRC6(codeValue, codeLen);
//      Serial.print("Sent RC6 ");
//      Serial.println(codeValue, HEX);
    }
  }

}
    else if (codeType == UNKNOWN /* i.e. raw */) {
     // Assume 38 KHz
      irsend.sendRaw(rawCodes, codeLen, 38);
      Serial.println("Sent raw");
    }
}
