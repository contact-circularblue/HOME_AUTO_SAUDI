void en_int()
{
  pinMode(ARDUINOPIN_1, INPUT); 
  enableInterrupt(ARDUINOPIN_1, interruptFunction_1, RISING);

  pinMode(ARDUINOPIN_2, INPUT); 
  enableInterrupt(ARDUINOPIN_2, interruptFunction_2, RISING);

  pinMode(ARDUINOPIN_3, INPUT); 
  enableInterrupt(ARDUINOPIN_3, interruptFunction_3, RISING);

  pinMode(ARDUINOPIN_4, INPUT); 
  enableInterrupt(ARDUINOPIN_4, interruptFunction_4, RISING);
  
}

