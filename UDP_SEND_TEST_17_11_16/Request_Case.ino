void Request_Case(int count)
{
  switch (count)
  {
    case 1:
      {
        //delay(2000);
        UDP.write("jackhammer,1,1");
        Serial.print("sending jackhammer,1,1");
        break;
      }
    case 2:
      {
        //delay(2000);
        UDP.write("jackhammer,1,0");
        Serial.print("sending jackhammer,1,0");
        break;
      }
    case 3:
      {
        //delay(2000);
        UDP.write("jackhammer,2,1");
        Serial.print("sending jackhammer,2,1");
        break;
      }
    case 4:
      {
        //delay(2000);
        UDP.write("jackhammer,2,0");
        Serial.print("sending jackhammer,2,0");
        break;
      }
    case 5:
      {
        //delay(2000);
        UDP.write("jackhammer,3,1");
        Serial.print("sending jackhammer,3,1");
        break;
      }
    case 6:
      {
        //delay(2000);
        UDP.write("jackhammer,3,0");
        Serial.print("sending jackhammer,3,0");
        break;
      }
    case 7:
      {
        //delay(2000);
        UDP.write("jackhammer,4,1");
        Serial.print("sending jackhammer,4,1");
        break;
      }
    case 8:
      {
        //delay(2000);
        UDP.write("jackhammer,4,0");
        Serial.print("sending jackhammer,4,0");
        break;
      }
  }
}
