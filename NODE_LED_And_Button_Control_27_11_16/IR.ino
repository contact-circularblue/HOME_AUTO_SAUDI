#include <IRremote.h>

void IR()
{
if (digitalRead(BUTTON_PIN) == LOW)
  {
    if (irrecv.decode(&results))
    {
      storeCode(&results);
      irrecv.resume();
    }
  }

  else if (digitalRead(BUTTON_PIN) == HIGH)
  {
    Serial.println("IR");
      Serial.println("Pressed, sending");
    sendCode();
    delay(50);
    while (digitalRead(BUTTON_PIN) == HIGH);
    irrecv.enableIRIn();
  }
}
