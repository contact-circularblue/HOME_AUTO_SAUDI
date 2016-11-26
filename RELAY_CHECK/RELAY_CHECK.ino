int LED_1 = 3;
int LED_2 = 4;
int LED_3 = 5;
int LED_4 = 6;
void setup() {
  // put your setup code here, to run once:
  pinMode (LED_1, OUTPUT);
  pinMode (LED_2, OUTPUT);
  pinMode (LED_3, OUTPUT);
  pinMode (LED_4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
  delay(2000);

  digitalWrite(4, HIGH);
  delay(2000);
  digitalWrite(4, LOW);
  delay(2000);

  digitalWrite(5, HIGH);
  delay(2000);
  digitalWrite(5, LOW);
  delay(2000);

  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(2000);
}
