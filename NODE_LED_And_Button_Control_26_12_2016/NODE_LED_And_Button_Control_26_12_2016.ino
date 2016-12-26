//turn on a LED when the button is pressed
//turn it off when the button is not pressed (or released)

#include <EEPROM.h>
#include <IRremote.h>
#include <EnableInterrupt.h>
#include <LinkedList.h>

LinkedList<int> myList = LinkedList<int>();

#define ARDUINOPIN_1 10
#define ARDUINOPIN_2 11
#define ARDUINOPIN_3 12
#define ARDUINOPIN_4 13

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

////////////////////////////////// IR initialisations
// Pin 3 default for IR LED
int RECV_PIN = A0;
int BUTTON_PIN = A1;
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

int listSize = 0;

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
  EEPROM.write(985, 0);
  listSize = EEPROM.read(985);///Linked List Size

  //irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);

  en_int();
  pinMode(LED_1, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_2, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_3, OUTPUT); //set the LED pin as OUTPUT
  pinMode(LED_4, OUTPUT); //set the LED pin as OUTPUT

  if (EEPROM.read(1) == 1)
    flag_1 = 1;
  else
    flag_1 = 0;

  if (EEPROM.read(2) == 1)
    flag_2 = 1;
  else
    flag_2 = 0;

  if (EEPROM.read(3) == 1)
    flag_3 = 1;
  else
    flag_3 = 0;

  if (EEPROM.read(4) == 1)
    flag_4 = 1;
  else
    flag_4 = 0;

  delay(2000); // when esp is switched on it sends some data,which is not required
}


int IR_test = 1;
void loop() {

  {
    IR();
  }

  data = "";
  if (Serial.available())
  {
    while (Serial.available())
    {
      data += char(Serial.read());
      delay(10);
    }
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
