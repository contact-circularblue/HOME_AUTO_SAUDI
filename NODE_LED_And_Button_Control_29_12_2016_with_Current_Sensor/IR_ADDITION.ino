
int IR_ADD()
{
  myList.clear();
  int value = 0;
  int POS = 0;
  int Flag = 0;
  ListSize = EEPROM.read(985);
//  Serial.print(" ListSize =");
//  Serial.println(ListSize);

  if (ListSize > 0 && ListSize < 13)
  {
//    Serial.println("Going in loop");
    
    for (int i = 0; i < ListSize; i++)
    {
      myList.add(EEPROM.read(986 + i));
    }

//    Serial.print("There are ");
//    Serial.print(ListSize);
//    Serial.print(" integers in the list.");
//    for (int h = 0; h < myList.size(); h++)
//    {
//      int val = myList.get(h);
//      Serial.print(val);
//      Serial.print("\t");
//    }
//
//    Serial.print(" myList.size()=");
//    Serial.println(myList.size());

    if (myList.size() == 1)
    {
      if (myList.get(0) > 1)
      {
        myList.add(0, 1);

        EEPROM.write(985, myList.size());
//        Serial.print("There are ");
//        Serial.print(EEPROM.read(985));
//        Serial.print(" integers in the list.");
//
//        for (int h = 0; h < myList.size(); h++)
//        {
//          int val = myList.get(h);
//          Serial.print(val);
//          Serial.print("\t");
//        }
        return 1;
      }
      else
      {
        myList.add(1, 2);

        EEPROM.write(985, myList.size());
        //        Serial.print("There are ");
        //        Serial.print(EEPROM.read(985));
        //        Serial.print(" integers in the list.");
        //
        //        for (int h = 0; h < myList.size(); h++)
        //        {
        //          int val = myList.get(h);
        //          Serial.print(val);
        //          Serial.print("\t");
        //        }
        return 2;
      }
    }
    else
    {
      for (int i = 0; i < ListSize - 1; i++)
      {
        int diff = myList.get(i++) - myList.get(i) ;
        if (diff > 1)
        {
          myList.add(i + 1, myList.get(i) + 1);
          value = myList.get(i) + 1;
          POS = i + 1;
          Flag = 1;
          break;
        }
      }
      if (Flag != 1)
      {
//        Serial.println("Flag not one");
        myList.add(ListSize, ListSize + 1);
        value = ListSize + 1;
        POS = ListSize;
      }
    }

//    Serial.println("Reached till here");
    EEPROM.write(985, myList.size());
//    Serial.print(" myList.size =");
//    Serial.println(EEPROM.read(985));

    for (int i = 0; i < myList.size(); i++)
    {
      EEPROM.write(986 + i, myList.get(i));
//      Serial.println(i);
    }

//    Serial.println("updated");
//
//    Serial.print("Element added = ");
//    Serial.println(value);
//    Serial.print("AT POS = ");
//    Serial.print(POS);

    return value;
  }

  else if (ListSize == 0)
  {
    EEPROM.write(986, 1); // update the first location
    EEPROM.write(985, 1);// update list size

    //    Serial.print(" 1st IR POS =");
    //    Serial.println(EEPROM.read(985));
    return 1;
  }

  else if (ListSize > 12)
  {
//    Serial.print("List Full");
  }
}
