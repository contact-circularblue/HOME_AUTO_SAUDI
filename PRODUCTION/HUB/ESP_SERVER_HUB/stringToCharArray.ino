char* stringToCharArray(String str)
{
  str.toCharArray(buf, 50);
  return buf;
}
char* stringToCharArray(String str,char *buffer)
{
  str.toCharArray(buffer, 50);
  return buffer;
}
