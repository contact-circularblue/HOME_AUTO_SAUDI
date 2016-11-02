/*

Measuring AC Current Using ACS712

*/

const int sensorIn = A0;

int mVperAmp = 66; // use 100 for 20A Module and 185 for 5 Module

float Voltage = 0;

float VRMS = 0;

float AmpsRMS = 0;

void setup(){

Serial.begin(9600);

}

void loop()

{

Voltage = getVPP();

VRMS = (Voltage/2.0) *0.707;

AmpsRMS = (VRMS * 1000)/mVperAmp;

Serial.print((AmpsRMS-0.10)*1000,3);
Serial.println(" Amps RMS");
Serial.print(VRMS);
Serial.println(" VRMS");

}

float getVPP()

{

float result;

int readValue; //value read from the sensor

int maxValue = 0; // store max value here

int minValue = 1023; // store min value here

uint32_t start_time = millis();

while((millis()-start_time) < 1000) //sample for 1 Sec

{

readValue = analogRead(sensorIn);

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

result = ((maxValue - minValue) * 5.0)/1023.0;

return result;

}
