void IR_DELETE(int IR_NUM)
{
  ListSize = EEPROM.read(985);

  for (int i = 0; i < ListSize; i++)
  {
    myList.add(EEPROM.read(986 + i));
  }

  for (int i = 0; i < ListSize; i++)
  {
    if (myList.get(i) == IR_NUM - 4);
    myList.remove(i);
  }

  EEPROM.update(985, myList.size());

  for (int i = 0; i < myList.size(); i++)
  {
    EEPROM.update(986 + i, myList.get(i));
  }
}

