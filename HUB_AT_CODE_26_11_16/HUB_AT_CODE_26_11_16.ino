#include<SoftwareSerial.h>

SoftwareSerial ESP_hub(10, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP_hub.begin(9600);
  //Serial.print("STARTING");


}

void loop() {
  // put your main code here, to run repeatedly:
  if (ESP_hub.available())
  {
  if (ESP_hub.find("hub_says:"))
    {
  //    Serial.print("1");
      delay(50);
    while(ESP_hub.available())
      {
      Serial.print(char(ESP_hub.read()));
      delay(1);
      }
    }
    
    //      Serial.print("jackhammer,0,2,0");
    //      delay(2000);
  }
  
  if(Serial.available())
  {
    delay(50);
    while(Serial.available())
      {
      ESP_hub.print(char(Serial.read()));
      delay(1);
      }
  }
}
//while(!Serial.find("ACK"));




