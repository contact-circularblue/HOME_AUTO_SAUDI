/*  Read AC Voltage 50 to 250 Volts - www.circuits4you.com
    Reads an analog input on pin 0, converts it to voltage, and prints the  
    result to the serial monitor.
    Graphical representation is available using serial plotter   (Tools > 
    Serial Plotter menu)
*/
int average=0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
 
  Serial.print(sensorValue);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 250V):
  float voltage = sensorValue * (240.0 / 1023.0);
  // print out the value you read:
  Serial.print("AC Voltage: ");
  Serial.print(voltage);
  Serial.println(" Volts");
  delay(10000);
}
 
