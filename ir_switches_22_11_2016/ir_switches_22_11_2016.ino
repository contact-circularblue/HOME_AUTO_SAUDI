/*
 * IRrecord: record and play back IR signals as a minimal 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected to the input BUTTON_PIN; this is the
 * send button.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include<EEPROM.h>
int RECV_PIN = 11;
int BUTTON_PIN_1 = 6;
int BUTTON_PIN_2 = 7;
int BUTTON_PIN_3 = 8;
int BUTTON_PIN_4 = 9;
//int BUTTON_PIN[4] = {5, 6, 7, 8};
int STATUS_PIN = 13;
int buttonState_1 =0; //digitalRead(BUTTON_PIN_1);
int buttonState_2 =0; //digitalRead(BUTTON_PIN_2);
int buttonState_3 =0; //digitalRead(BUTTON_PIN_3);
int buttonState_4 =0; //digitalRead(BUTTON_PIN_4);
int j=0;

  

IRrecv irrecv(RECV_PIN);
IRsend isend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(STATUS_PIN, OUTPUT);
  
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long a=255;
unsigned long b=65280;
unsigned long c=983040;
unsigned long ans;
unsigned long ans1;
unsigned long ans11;
unsigned long ans2;
unsigned long ans21;
unsigned long t,t1;
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw
//byte a;
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state

// Stores the code for later playback
// Most of this code is just logging
void storeCode(decode_results *results) {
  codeType = results->decode_type;
  int count = results->rawlen;
  /*if (codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
    }
    Serial.println("");
  }
  else {*/
    if (codeType == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    } 
    else if (codeType == SONY) {
      Serial.print("Received SONY: ");
    } 
//    else if (codeType == PANASONIC) {
//      Serial.print("Received PANASONIC: ");
//    }
//    else if (codeType == JVC) {
//      Serial.print("Received JVC: ");
//    }
    else if (codeType == RC5) {
      Serial.print("Received RC5: ");
    } 
    else if (codeType == RC6) {
      Serial.print("Received RC6: ");
    } 
    /*else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println("");
    }*/
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;
    hello();
  //}
}

void hello()
{
    ans=codeValue & a;
    Serial.println(ans, HEX);
    ans1=codeValue & b;
    //Serial.println(ans1, HEX);
    ans11=ans1>>8;
    Serial.println(ans11, HEX);
    ans2=codeValue & c;
    //Serial.println(ans2, HEX);
    ans21=ans2>>16;
    Serial.println(ans21, HEX);
    //a=(byte)codeValue;
    //sendCommand(codeValue);
    //Serial.println(codeValue, HEX);
    //a=(codeValue)
   
   for(int i=0; i<1;i++)
   {
    EEPROM.write(i+j,codeLen);
    EEPROM.write(i+j+1,ans);
    EEPROM.write(i+j+2,ans11);
    EEPROM.write(i+j+3,ans21);
   }
   j+=50;
    //t=t|ans;
    //Serial.println(t,HEX);
    //EEPROM.write(4,t);
}


unsigned long combine(int a,int b,int c)
{
  unsigned long t=c;
  t<<=16;
  //Serial.println(t,HEX);
  unsigned long t1=b;
  t1<<=8;
  t=t|t1|a;
  return t;
}

void sendCode(int repeat) {

  int m=0;

  if(buttonState_1)
  {
    //u=,v=,w=,x=;
   m=0;
  }
  else if(buttonState_2)
  {
   // k=,l=,m=,n=;
   m=50;
  }
  else if(buttonState_3)
  {
   // k=,l=,m=,n=;
   m=100;
  }
  else if(buttonState_4)
  {
    //k=,l=,m=,n=;
   m=150;
  }
  
  if(buttonState_1==HIGH||buttonState_2==HIGH||buttonState_3==HIGH||buttonState_4==HIGH)
      {
        int k=EEPROM.read(m+1);
        int k1=EEPROM.read(m+2);
        int k2=EEPROM.read(m+3);
        //Serial.println(k,HEX);
        //Serial.println(k1,HEX);
        //Serial.println(k2,HEX);
        unsigned long p=combine(k,k1,k2);
        Serial.println(p, HEX);
        codeValue=p;
        codeLen=EEPROM.read(m);
     }
  if (codeType == NEC) {
    if (repeat) {
      irsend.sendNEC(REPEAT, codeLen);
      Serial.println("Sent NEC repeat");
      
    } 
    else {
      irsend.sendNEC(codeValue, codeLen);
      Serial.print("Sent NEC ");
      Serial.println(codeValue, HEX);
    }
  } 
  else if (codeType == SONY) {
    irsend.sendSony(codeValue, codeLen);
    Serial.print("Sent Sony ");
    Serial.println(codeValue, HEX);
  } 
//  else if (codeType == PANASONIC) {
//    irsend.sendPanasonic(codeValue, codeLen);
//    Serial.print("Sent Panasonic");
//    Serial.println(codeValue, HEX);
//  }
//  else if (codeType == JVC) {
//    irsend.sendPanasonic(codeValue, codeLen);
//    Serial.print("Sent JVC");
//    Serial.println(codeValue, HEX);
//  }
  else if (codeType == RC5 || codeType == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      toggle = 1 - toggle;
    }
    // Put the toggle bit into the code to send
    codeValue = codeValue & ~(1 << (codeLen - 1));
    codeValue = codeValue | (toggle << (codeLen - 1));
    if (codeType == RC5) {
      Serial.print("Sent RC5 ");
      Serial.println(codeValue, HEX);
      irsend.sendRC5(codeValue, codeLen);
    } 
    else {
      irsend.sendRC6(codeValue, codeLen);
      Serial.print("Sent RC6 ");
      Serial.println(codeValue, HEX);
    }
  } 
  else if (codeType == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    irsend.sendRaw(rawCodes, codeLen, 38);
    Serial.println("Sent raw");
  }
}




void sendCommand(unsigned long command){
  for (unsigned long  mask = 65536UL; mask>=1UL;  mask >>= 1) {

    if (command & mask) {

    Serial.print( "1" );
    } else {

    Serial.print( "0" );
    }
  }
}




int lastButtonState;

void loop() {
  // If button pressed, send the code.
  buttonState_1 = digitalRead(BUTTON_PIN_1);
  buttonState_2 = digitalRead(BUTTON_PIN_2);
  buttonState_3 = digitalRead(BUTTON_PIN_3);
  buttonState_4 = digitalRead(BUTTON_PIN_4);
  
  if (lastButtonState == HIGH && (buttonState_1 == LOW||buttonState_2 == LOW||buttonState_3 == LOW||buttonState_4 == LOW)) {
    Serial.println("Released");
    irrecv.enableIRIn(); // Re-enable receiver
  }

  if (buttonState_1||buttonState_2||buttonState_3||buttonState_4) {
    Serial.println("Pressed, sending");
    digitalWrite(STATUS_PIN, HIGH);
    sendCode(lastButtonState == buttonState_1||lastButtonState == buttonState_2||lastButtonState == buttonState_3||lastButtonState == buttonState_4);
    digitalWrite(STATUS_PIN, LOW);
    delay(50); // Wait a bit between retransmissions
  } 
  else if (irrecv.decode(&results)) {
    digitalWrite(STATUS_PIN, HIGH);
    storeCode(&results);
    irrecv.resume(); // resume receiver
    digitalWrite(STATUS_PIN, LOW);
  }
  lastButtonState = buttonState_1;
}
