//turn on a LED when the button is pressed
//turn it off when the button is not pressed (or released)

#include <EEPROM.h>
#include <EnableInterrupt.h>
#define ARDUINOPIN_1 10
#define ARDUINOPIN_2 11
#define ARDUINOPIN_3 12
#define ARDUINOPIN_4 13

volatile uint16_t interruptCount=0; // The count will go back to 0 after hitting 65535.

bool flag_1;
bool flag_2;
bool flag_3;
bool flag_4;

int LED_1 = 4; //the pin we connect the LED
int LED_2 = 5; //the pin we connect the LED 
int LED_3 = 6; //the pin we connect the LED
int LED_4 = 7; //the pin we connect the LED

void setup() {
/*
  EEPROM.write(1,0);
  EEPROM.write(2,0);
  EEPROM.write(3,0);
  EEPROM.write(4,0);
*/
  Serial.begin(115200);
  en_int();
  pinMode(LED_1, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_2, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_3, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_4, OUTPUT); //set the LED pin as OUTPUT

  if(EEPROM.read(1)==1)
  flag_1=1;
  else
  flag_1=0;

  if(EEPROM.read(2)==1)
  flag_2=1;
  else
  flag_2=0;
  
  if(EEPROM.read(3)==1)
  flag_3=1;
  else
  flag_3=0;
  
  if(EEPROM.read(4)==1)
  flag_4=1;
  else
  flag_4=0;

  

}
 
void loop() {

  Serial.println("---------------------------------------");
  delay(1000);
  Serial.print("Pin was interrupted: ");
  Serial.print(interruptCount, DEC);
  Serial.println(" times so far.");
  Serial.print("EEPROM contains:");
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(4));
}
