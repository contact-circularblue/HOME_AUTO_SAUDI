void Raw_Code_Add(int list_pos)
{
  j = list_pos * 80;
  EEPROM.write(j, codeLen);
  j++;
  EEPROM.write(j, codeType);
  int n;
  n = codeLen;
  for (int i = 0; i < n; i++)
  {
    EEPROM.write(i + j, UnknownCodes[i]);   // j is global
    //    Serial.print(UnknownCodes[i]);
    delay(10);
  }
  // Serial.print("Unknown Success");
}

