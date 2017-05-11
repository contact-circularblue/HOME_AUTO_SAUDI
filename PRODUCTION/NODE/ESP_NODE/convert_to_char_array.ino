#include <Arduino.h>

void convert_to_char(String a, char* b)
{
  a.toCharArray(b, a.length() + 1);
}
