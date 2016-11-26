void sendCode(int repeat) {
  
  int m=0;
  if(buttonState)
  {
   m=0;
  }

/* if(buttonState==HIGH)
      {
        int k=EEPROM.read(m+1);
        int k1=EEPROM.read(m+2);
        int k2=EEPROM.read(m+3);
        unsigned long p=combine(k,k1,k2);
        Serial.println(p, HEX);
        codeValue=p;
        codeLen=EEPROM.read(m);
     }
*/  
  
  if (codeType == NEC) {
    if (repeat) {
      irsend.sendNEC(REPEAT, codeLen);
      Serial.println("Sent NEC repeat");
    }
    else {
      irsend.sendNEC(codeValue, codeLen);
      Serial.print("Sent NEC ");
      Serial.println(codeValue, HEX);
    }
  }
  else if (codeType == SONY) {
    irsend.sendSony(codeValue, codeLen);
    Serial.print("Sent Sony ");
    Serial.println(codeValue, HEX);
  }
  else if (codeType == RC5 || codeType == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      toggle = 1 - toggle;
    }
    // Put the toggle bit into the code to send
    codeValue = codeValue & ~(1 << (codeLen - 1));
    codeValue = codeValue | (toggle << (codeLen - 1));
    if (codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue, HEX);
      irsend.sendRC5(codeValue, codeLen);
    }
    else {
      irsend.sendRC6(codeValue, codeLen);
      Serial.print("Sent RC6 ");
      Serial.println(codeValue, HEX);
    }
  }
//  else if (codeType == UNKNOWN /* i.e. raw */) {
//    // Assume 38 KHz
//    irsend.sendRaw(rawCodes, codeLen, 38);
//    Serial.println("Sent raw");
//  }
}
