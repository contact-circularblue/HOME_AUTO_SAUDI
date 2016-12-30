void IR_DELETE(int IR_NUM)
{
  Serial.print("IR_NUM =");
  Serial.println(IR_NUM);

  myList.clear();
  ListSize = EEPROM.read(985);

  for (int i = 0; i < ListSize; i++)
  {
    myList.add(EEPROM.read(986 + i));
  }

  for (int i = 0; i < myList.size(); i++)
  {
    Serial.print(myList.get(i));
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("myList.size()= ");
  Serial.println(myList.size());

  Serial.print("ListSize= ");
  Serial.println(ListSize);

  for (int i = 0; i < ListSize; i++)
  {
    if (myList.get(i) == IR_NUM - 4);
    {
      Serial.print("deleted =");
      Serial.println(myList.get(i));
      myList.remove(i);
      break;
    }
  }

  EEPROM.write(985, myList.size());

  Serial.print("There are ");
  Serial.print(EEPROM.read(985));
  Serial.print(" integers in the list. ");

  for (int i = 0; i < myList.size(); i++)
  {
    EEPROM.write(986 + i, myList.get(i));
    int val = EEPROM.read(986 + i) + 4;
    Serial.print(val);
    Serial.print("\t");
  }
}

