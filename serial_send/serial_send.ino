void setup() {
  //Serial.begin(115200);
  Serial.begin(9600);
}

void loop() {
  /*
    Serial.print("1,1");
    delay(2000);
    Serial.print("1,0");
    delay(2000);

    Serial.print("2,1");
    delay(2000);
    Serial.print("2,0");
    delay(2000);

    Serial.print("3,1");
    delay(2000);
    Serial.print("3,0");
    delay(2000);

    Serial.print("4,1");
    delay(2000);
    Serial.print("4,0");
    delay(2000);*/

  //Serial.println("Received packet of size 14");
  Serial.println("From 192.168.1.4:80");
  //Serial.println("Contents:");
  Serial.println("jackhammer_1, 1");
  //Serial.println("I got it");
  Serial.println("1,1");

delay(2000);
  //Serial.flush();
}
