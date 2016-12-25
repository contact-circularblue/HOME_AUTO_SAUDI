void Raw_Code_Add(int list_pos)
{
  j = list_pos * 80;
  EEPROM.write(j, codeLen);
  j++;
  EEPROM.write(j, codeType);
  int n;
  n = codeLen;
 // byte Save_unknown[80]; 

  for (int i = 0; i < n; i++)
  {
   // Save_unknown[i]= UnknownCodes[i];
    
    EEPROM.write(i + j, UnknownCodes[i]);   // j is global
  //  Serial.print(UnknownCodes[i]);
    delay(10);
  }

 // Serial.print("Unknown Success");
}

