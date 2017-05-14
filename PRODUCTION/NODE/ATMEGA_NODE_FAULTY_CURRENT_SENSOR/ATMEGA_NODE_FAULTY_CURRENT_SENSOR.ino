//turn on a LED when the button is pressed
//turn it off when the button is not pressed (or released)

#include <EEPROM.h>
#include <TimerOne.h>	
#include <IRremote.h>
#include <EnableInterrupt.h>
#include <LinkedList.h>0,
//#include <SoftwareSerial.h>

//SoftwareSerial node_add(8, 9);

String NODE_ID = "4WQt8Wn0y8";

ISR(TIMER1_OVF_vect);

LinkedList<int> myList = LinkedList<int>();

#define ARDUINOPIN_1 10
#define ARDUINOPIN_2 11
#define ARDUINOPIN_3 12
#define ARDUINOPIN_4 A1

String SSID = "";
String password = "";

// FOR LINKED LIST
//int ListSize=0;
int ListSize;
int timer_ISR=0;
int calibration=0;


// For Current Sensor

const int sensorIn = A5;

int mVperAmp = 66; // use 100 for 20A Module and 185 for 5 Module

float Voltage = 0;

float VRMS = 0;

float AmpsRMS = 0;

volatile uint16_t interruptCount = 0; // The count will go back to 0 after hitting 65535.

char max_devices = '4';

bool flag_1;
bool flag_2;
bool flag_3;
bool flag_4;

int LED_1 = 4; //the pin we connect the LED
int LED_2 = 5; //the pin we connect the LED
int LED_3 = 6; //the pin we connect the LED
int LED_4 = 7; //the pin we connect the LED

String Send_to_ESP = "";
String data = "";

char action = 0;
////////////////////////////////// Timer

unsigned long previousMillis = 0;
const long interval = 15000;

////////////////////////////////// IR initialisations
// Pin 3 default for IR LED
int RECV_PIN = A0;
//int BUTTON_PIN = A1;
int STATUS_PIN = 13;

int node_switch = 0;
int state = 0;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

int codeType = -1; // The type of code
unsigned long a = 255;
unsigned long b = 65280;
unsigned long c = 983040;

unsigned long byte_code;
unsigned long byte_1;
unsigned long byte_2;
unsigned long byte_3;

int buttonState;
int j = 0; // used in CODE_BYTE_SEPERATOR


unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw
byte UnknownCodes[80];
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state
int lastButtonState;

//int listSize = 0;

/////////////////////////////////

void setup() {
  /*
    EEPROM.write(1,0);
    EEPROM.write(2,0);
    EEPROM.write(3,0);
    EEPROM.write(4,0);
  */
  //Serial.begin(115200);
  delay(2000);
  Serial.begin(9600);
  Serial.flush();

  calibrate_current_sensor();

  //EEPROM.update(985, 0);
  // ListSize = EEPROM.read(985);
  // listSize = EEPROM.read(985);///Linked List Size


  //irrecv.enableIRIn(); // Start the receiver
  //pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);

  en_int();
  pinMode(LED_1, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_2, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_3, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_4, OUTPUT); //set the LED pin as OUTPUT

  if (EEPROM.read(1001) == 1)
    //flag_1 = 1;
    digitalWrite(4, HIGH);
  else
    // flag_1 = 0;
    digitalWrite(4, LOW);

  if (EEPROM.read(1002) == 1)
    //flag_2 = 1;
    digitalWrite(5, HIGH);
  else
    //flag_2 = 0;
    digitalWrite(5, LOW);

  if (EEPROM.read(1003) == 1)
    //flag_3 = 1;
    digitalWrite(6, HIGH);
  else
    //flag_3 = 0;
    digitalWrite(6, LOW);

  if (EEPROM.read(1004) == 1)
    //flag_4 = 1;
    digitalWrite(7, HIGH);
  else
    //flag_4 = 0;
    digitalWrite(7, LOW);

  delay(2000); // when esp is switched on it sends some data,which is not required
}


int IR_test = 1;
void loop() {

  //  {
  //    IR();
  //  }

  data = "";
  if (Serial.available())
  {
    while (Serial.available())
    {
      data += char(Serial.read());
      delay(10);
    }

    //    Serial.print("data:");
    //    Serial.println(data);

    delay(1000);

    //    while(1);

    if (data.indexOf("node_add") != -1)
    {



      delay(100);
      Serial.print("ID:");
      Serial.print(NODE_ID);

      delay(300);
      if (Serial.find("SSID:"))
      {
        while (Serial.available())
        {
          SSID += char(Serial.read());
          delay(3);
        }
        
//        Serial.println("SSID found:");
//        Serial.println(SSID);

        delay(20);
        Serial.print("OK");
        delay(500);
        if (Serial.find("::PASSWORD::"))
        {
          while (Serial.available())
          {
            password += char(Serial.read());
            delay(3);
          }
          Serial.print("OK");

          delay(1000);
          Serial.print("SSID:");
          Serial.print(SSID);
          Serial.print("::password::");
          Serial.print(password);
          Serial.print(":::END::");
          SSID = "";
          password = "";
        }
      }
    }

    //Serial.println("data= "+data);
    //    Serial.print("data received=" + data);
    //////////////////Serial.println();
    action = data.charAt(0);
    String temp1 = data.substring(data.indexOf(",") + 1);
    //Serial.println("temp1=" + temp1);
    String temp2 = temp1.substring(0, temp1.indexOf(","));
    //Serial.println("temp2=" + temp2);
    String temp3 = temp1.substring(temp1.indexOf(",") + 1);
    // Serial.println("temp3=" + temp3);


    node_switch = temp2.toInt();
    state = temp3.toInt();

    //      Serial.println(node_switch);
    //      Serial.println(state);
    actuate(action, node_switch, state);

    // toggle_LED(); // reflects the changes made by the mobile app.
    //delay(200);

  }




}
