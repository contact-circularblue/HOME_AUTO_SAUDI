unsigned long t=4;


void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

t <<= 8;
Serial.print("value after shift is: ");
Serial.print(t);

while(1);
}
