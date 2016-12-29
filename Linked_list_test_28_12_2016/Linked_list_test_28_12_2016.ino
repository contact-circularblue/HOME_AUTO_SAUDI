/*
	LinkedList Example
	Link: http://github.com/ivanseidel/LinkedList

	Example Created by
		Tom Stewart, github.com/tastewar

	Edited by:
		Ivan Seidel, github.com/ivanseidel
*/
#include <LinkedList.h>

LinkedList<int> myList = LinkedList<int>();
int j = myList.size();

void setup()
{

  Serial.begin(9600);
  Serial.println("Hello!");

  // Add some stuff to the list

  myList.add(0);
  myList.add(50);
  myList.add(100);
  myList.add(150);
  myList.add(200);
  myList.add(250);
}

void loop() {

  int listSize = myList.size();

  Serial.print("There are ");
  Serial.print(listSize);
  Serial.print(" integers in the list.");
  
   for (int h = 0; h < myList.size(); h++) 
  {

    // Get value from list
    int val = myList.get(h);

    // If the value is negative, print it

    Serial.print(val);
    Serial.print("\t");
  }
  
  Serial.println();
  Serial.print("There are ");
  Serial.print(myList.size());
  Serial.println(" integers in the list.");
  
  int val = myList.remove(2);
  
  for (int h = 0; h < myList.size(); h++) 
  {

    // Get value from list
    int val = myList.get(h);

    // If the value is negative, print it

    Serial.print(val);
    Serial.print("\t");
  }

    // If the value is negative, print it
Serial.println();
Serial.print("There are ");
  Serial.print(myList.size());
  Serial.println(" integers in the list.");
    
    

myList.add(2,99);
  
  for (int h = 0; h < myList.size(); h++) 
  {

    // Get value from list
    int val = myList.get(h);

    // If the value is negative, print it

    Serial.print(val);
    Serial.print("\t");
  }

Serial.println();
Serial.print("There are ");
  Serial.print(myList.size());
  Serial.println(" integers in the list.");


while(1);

}


