void calibrate_current_sensor()
{
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  float power_local[5];
  for(int i=0;i<5;i++)
  {
    power_local[i]=measure_current();
//    Serial.print("returned sum=");
//    Serial.println(power_local[i]);
  }
  float avg_power_local=(power_local[0]+power_local[1]+power_local[2])/3;
//  Serial.print("avg_power_local=");
//  Serial.println(avg_power_local);
  if(avg_power_local<0)
  {
    EEPROM.write(1005,0);
    EEPROM.put(1006, (-avg_power_local));
//    Serial.println("+");
  }

  else if(avg_power_local>0)
  {
    EEPROM.write(1005,1);
    EEPROM.put(1006, (avg_power_local));
//    Serial.println("-");
  }

  

  calibration=1;

//  while(1);
  
  
}

