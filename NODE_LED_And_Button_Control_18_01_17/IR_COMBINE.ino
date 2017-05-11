unsigned long combine(int code_size, int *combine_byte)
{
   
  unsigned long t = 0;
  //Serial.println("array in function is:");

  for (int i = code_size - 1 ; i >= 0; i--)
  {
    unsigned long t2 = 0;
    long shift = 8 * i ;
   // Serial.print("value of shift is: ");
   // Serial.println(shift);
   // Serial.print("value to shift is: ");
   // Serial.println(combine_byte[i]);

    t2 = combine_byte[i];

    if (i == 1)
      t2 <<= 8;
    else
      t2 <<= shift;

   // Serial.print("value after shift is: ");
   // Serial.println(t2);

    t = t | t2;
  //  Serial.print("value after oring is: ");
  //  Serial.println(t);
  }
 // Serial.print("recombined code is :");
 // Serial.println(t, HEX);
  return t;

  
  
}

