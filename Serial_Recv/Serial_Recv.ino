String data_from_switch = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  bool count = 0;

  while (Serial.available())
  {
    data_from_switch += char(Serial.read());
    count = 1;
  }

  if (count == 1)
  {
    //        if (data_from_switch.charAt(0) >= 49 && data_from_switch.charAt(0) <= 52)
    //        {
    //          if (data_from_switch.charAt(2) == 48 || data_from_switch.charAt(2) == 49)
    //          {
    //Serial.println("data_from_switch is: ");
    Serial.print(data_from_switch);
    //          }
    //        }
    //        else
    //Serial.println("invalid data send");
   
  }
   data_from_switch = "";
}
