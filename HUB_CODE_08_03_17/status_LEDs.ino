void status_LEDs(int led)
{
  switch (led)
  {
    case 0: //Wifi LED ON, rest OFF
      digitalWrite(4, HIGH);
      digitalWrite(14, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(12, HIGH);
      break;

    case 1: //Wifi LED ON, rest OFF
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(14, HIGH);
      break;


    case 2: //Server LED ON, rest OFF
      digitalWrite(12, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(14, HIGH);
      digitalWrite(2, HIGH);
      break;


    case 3: //WebSockets LED ON, rest OFF
      digitalWrite(4, LOW);
      digitalWrite(14, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(12, HIGH);
      break;


    case 4: //NodeAddition LED ON
      digitalWrite(14, LOW);
      break;

    case 5: //NodeAddition LED OFF
      digitalWrite(14, HIGH);
      break;

  }

}

