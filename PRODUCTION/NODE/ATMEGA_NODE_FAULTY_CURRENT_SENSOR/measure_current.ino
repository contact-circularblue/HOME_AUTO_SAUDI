float measure_current()
{
  float sum = 0;
  for (int i = 0; i < 20; i++)
  {
    //  Serial.println(i);
    Voltage = getVPP();
    //      Serial.print("result=");
    //      Serial.println(Voltage);

    VRMS = (Voltage / 2.0) * 0.707;

    AmpsRMS = (VRMS * 1000) / mVperAmp;

    sum = (sum ) + AmpsRMS;
  }

  sum = sum / 20; //Averaging

  if (calibration == 1)
  {
    //    Serial.print("sum original=");
    //    Serial.println(sum, 5);
    //    Serial.println(EEPROM.read(1005));

    if (EEPROM.read(1005) == 0)
    {
      float factor = 0;
      EEPROM.get(1006, factor);
      //      Serial.println(factor);
      sum = sum + factor;
    }
    else if (EEPROM.read(1005) == 1 )
    {
      float factor = 0;
      EEPROM.get(1006, factor);
      //      Serial.println(factor);
      sum = sum - factor;
    }
  }
  //  if(sum<0)
  //  {
  //    sum=-sum;
  //  }
  //  sum = sum-0.9;

  //sum=sum+0.05 ;
  //sum=sum/1000;// Conver to Amps from mAmps

  //  Serial.print("sum=");
  //  Serial.println(sum);

  float power = sum * 230;

  if (power < 0)
  {
    power = -power;
  }

  if (EEPROM.read(1001) == 0 && EEPROM.read(1002) == 0 && EEPROM.read(1003) == 0 && EEPROM.read(1004) == 0)
  {
    power = 4.0;
  }
  if (calibration == 1)
  {
    int devices_on = 0;
    for (int i = 0; i < 4; i++)
    {
      if (EEPROM.read(1000 + i) == 1)
      {
        devices_on++;
      }
    }
    //    Serial.print("devices_on=");
    //    Serial.println(devices_on);
    if (devices_on > 1)
    {
      power = ((power * (40 - power) * ((devices_on) * 10)) / 60);
      //      Serial.print("power=");
      //    Serial.println(power);
      if (power < 0)
        power = -power;
    }
    return power;
  }
  else
  {
    return sum;
  }
}

float getVPP()

{

  float result;

  int readValue; //value read from the sensor

  int maxValue = 0; // store max value here

  int minValue = 1023; // store min value here

  uint32_t start_time = millis();

  while ((millis() - start_time) < 100) //sample for 1 Sec

  {

    readValue = analogRead(sensorIn);
    //    Serial.print("A0=");
    //    Serial.println(readValue);
    readValue -= 440;

    // see if you have a new maxValue

    if (readValue > maxValue)

    {

      /*record the maximum sensor value*/

      maxValue = readValue;

    }

    if (readValue < minValue)

    {

      /*record the maximum sensor value*/

      minValue = readValue;

    }

  }

  // Subtract min from max

  result = ((maxValue - minValue) * 3) / 1023.0;

  return result;

}
