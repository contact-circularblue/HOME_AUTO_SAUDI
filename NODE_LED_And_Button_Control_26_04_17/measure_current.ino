float measure_current()
{
  float sum=0;
  for (int i=0;i<20;i++)
{
//  Serial.println(i);
Voltage = getVPP();

VRMS = (Voltage/2.0) *0.707;

AmpsRMS = (VRMS * 1000)/mVperAmp;

sum=(sum-0.10)+AmpsRMS;
}

sum=sum/10;//Averaging
//sum=sum-0.10;
//sum=sum/1000;// Conver to Amps from mAmps
float power=sum*230;

if(power<0)
power=0;

 return power;
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
    readValue-=440;

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
