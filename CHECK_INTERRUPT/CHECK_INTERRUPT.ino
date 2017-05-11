const byte interruptPin = 2;  

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Send_Reset, RISING);  // for sending reset to both ESP's
}

void loop() {
  // put your main code here, to run repeatedly:
delay(10);
}

void Send_Reset()
{
  Serial.print("RESET_ESP");
  delay(100);
//  ESP_hub.print("RESET_ESP");
}

