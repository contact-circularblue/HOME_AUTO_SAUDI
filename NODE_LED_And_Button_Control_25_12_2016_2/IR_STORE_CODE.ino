// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results, int pos_list) {

  //Serial.println("STORING-----");
  codeType = results->decode_type;
  int count = results->rawlen;
  if (codeType == UNKNOWN) {          ////////////////////////////////////////////////
//    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
       // rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK - MARK_EXCESS;
        UnknownCodes[i - 1] = results->rawbuf[i];
//        Serial.print(" m");
      }
      else {
        // Space
       // rawCodes[i - 1] = results->rawbuf[i] * USECPERTICK + MARK_EXCESS;
        UnknownCodes[i - 1] = results->rawbuf[i];        
//        Serial.print(" s");
      }
//      Serial.print(rawCodes[i - 1], DEC);
    }

    Raw_Code_Add(pos_list);
    //    Serial.println("");
//    Serial.println("Raw Code Saved");
    
//    Code_byte_Seperate(pos_list);
//    Serial.println("");
  }

  /*
  else {     
    if (codeType == NEC) {
//      Serial.print("Received NEC: ");
//
//      Serial.println("HEX is printing");
//    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

//    Serial.println("code length is: ");
//    Serial.println(codeLen);

    Code_byte_Seperate(pos_list);
    
      if (results->value == REPEAT) {
        
        // Don't record a NEC repeat value as that's useless.
//        Serial.println("repeat; ignoring.");
        return;
      }
    }
  //  }
    else if (codeType == SONY) {
//      Serial.print("Received SONY: ");
//      Serial.println("HEX is printing");
//    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

//    Serial.println("code length is: ");
//    Serial.println(codeLen);

    Code_byte_Seperate(pos_list);
    
    }
    else if (codeType == RC5) {
//      Serial.print("Received RC5: ");
//      Serial.println("HEX is printing");
//    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

//    Serial.println("code length is: ");
//    Serial.println(codeLen);

    Code_byte_Seperate(pos_list);
    
    }
    else if (codeType == RC6) {
//      Serial.print("Received RC6: ");
//      Serial.println("HEX is printing");
//    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;

//    Serial.println("code length is: ");
//    Serial.println(codeLen);

    Code_byte_Seperate(pos_list);
    
    }
//   else {
//      Serial.print("Unexpected codeType ");
//      Serial.print(codeType, DEC);
//      Serial.println("");
//    }
    
    
 // }
}
*/
}


