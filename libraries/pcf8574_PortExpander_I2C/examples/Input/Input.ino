#include <PortExpander_I2C.h>
#include "Wire.h"

PortExpander_I2C pe(0x20);


void setup() {  
  pe.init();
  Serial.begin(9600);
  for( int i = 0; i < 8; i++ ){
    pe.pinMode(i,INPUT);
  }
  pinMode(4,INPUT);
}

void loop() {
  
  byte k=0;
  
  if(digitalRead(4)==HIGH)
  {
    while(digitalRead(4)==HIGH);
    //pe.digitalRead(i);
    Wire.requestFrom(32,1);
    if(Wire.available())     //If the request is available
    {
        k=Wire.read();       //Receive the data
    }
    
  //if(k=='1') 
  Serial.println(char(k));
  
  Serial.print("\n\n");
  //delay(5000);
  }
  //while(1);
}
