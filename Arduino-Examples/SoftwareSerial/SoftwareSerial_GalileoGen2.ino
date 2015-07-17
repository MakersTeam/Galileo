/*
SoftwareSerial_GalileoGen2.ino - SoftwareSerial on GalileoGen2

Since the SoftwareSerial.h library is not supported in the Galileo board, this examples shows a
workaround of it. This sketch only works on Galileo Gen2.

Prior to run the sketch, the library SoftwareSerial_Class.h has to be imported.
Only pins 2 and 3 can be used for this purpose.

This example code is in the public domain.

Revision History

----------------------------------------------------------
    Author		   Date		  Description
----------------------------------------------------------
Diego Villalobos	07-17-2015	Example created

*/

 #include <SoftwareSerial_Class.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);   // The "Serial" object is for the Serial Monitor output.
  Serial1.begin(9600);  // The "Serial1" object is for the pins 0 and 1.
  mySerial.begin(9600); // The "mySerial" object is for the pins 2 and 3. 
}

void loop() // Run over and over
{
  Serial.println("Sending from mySerial to Serial1...");
  mySerial.println(0b00000000);  // Sends data.
  Serial.println("Receiving in Serial1 from mySerial...");  
  
  while(Serial1.available()){
    Serial.println("Printing..."); 
    Serial.println(Serial1.read(),DEC);  // Data received and printed in the Serial Monitor.
  }
  
  delay (2500);
  
  Serial.println("Sending from Serial1 to mySerial...");
  Serial1.println(0b11111111);  // Sends data.
  Serial.println("Receiving in mySerial from Serial1...");  
  
  while(mySerial.available()){
    Serial.println("Printing...");
    Serial.println(mySerial.read(),DEC);  // Data received and printed in the Serial Monitor.
  }
  
  delay (2500);
}
