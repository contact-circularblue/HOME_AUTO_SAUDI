// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results) {

  //Serial.println("STORING-----");
  codeType = results->decode_type;
  int count = results->rawlen;
/*  if (codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
  }
  else {*/
    if (codeType == NEC) {
      Serial.print("Received NEC: ");

      Serial.println("HEX is printing");
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

    Serial.println("code length is: ");
    Serial.println(codeLen);

    Code_byte_Seperate();
    
      if (results->value == REPEAT) {
        
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    }
    else if (codeType == SONY) {
      Serial.print("Received SONY: ");
      Serial.println("HEX is printing");
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

    Serial.println("code length is: ");
    Serial.println(codeLen);

    Code_byte_Seperate();
    
    }
    else if (codeType == RC5) {
      Serial.print("Received RC5: ");
      Serial.println("HEX is printing");
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

    Serial.println("code length is: ");
    Serial.println(codeLen);

    Code_byte_Seperate();
    
    }
    else if (codeType == RC6) {
//      Serial.print("Received RC6: ");
//      Serial.println("HEX is printing");
//    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

//    Serial.println("code length is: ");
//    Serial.println(codeLen);

    Code_byte_Seperate();
    
    }
   /* else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println("");
    }*/
    
    
 // }
}


