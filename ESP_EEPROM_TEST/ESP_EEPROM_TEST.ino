#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.begin(512);
}

void loop() {
  // put your main code here, to run repeatedly:
  String save_me = "ESP_8266";
  for (int i = 0; i < save_me.length(); i++)
  {
    EEPROM.write(i, save_me.charAt(i));
    delay(100);
    EEPROM.commit();
  }

  Serial.println("Reading From EEPROM_ESP");

  for (int i = 0; i < save_me.length(); i++)
  {
    Serial.println(char(EEPROM.read(i)));
    delay(100);
  }

}
