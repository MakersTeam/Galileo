/*
DataSharing.ino - Data sharing between environments on Galileo board

This example shows how to send data from Linux side to the Arduino side in
order to be manipulated through a variable.

This example has been tested on a Galileo Gen2.

This example code is in the public domain.

Revision History
----------------------------------------------------------
    Author		   Date		  Description
----------------------------------------------------------
Diego Villalobos	07-28-2015	Example created

*/

FILE *sys_info_file;
int c;
String info;

String getInfo(){
  /* 
     Create a file in Linux side with the data desired. Then open that file from the 
     Arduino sketch, read and return the content. The file created is deleted before
     returning the value read.
  */
  
  String file_output;
  
  system("uname -a > /home/sys_info.txt");
  
  sys_info_file = fopen("/home/sys_info.txt","r");
  
  if (sys_info_file)
  {
    while ((c = getc(sys_info_file)) != EOF) // Keep reading until the end of the file
    {
      if(c != 10) // Detect if it is a new line character
      {
           file_output += (char)c; // Only the last line will be returned. Modify this for custom purposes.
      }
    }
    fclose(sys_info_file);
   }  
  
  // Delete the file created in the Linux side
  system("rm /home/sys_info.txt");
  
  // Return the data read 
  return file_output;
}

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Store the data from the Linux side in a variable
  String info = getInfo();
  
  // Manipulate the data and print it in the Serial Monitor.
  Serial.print("Kernel name: ");
  Serial.println(info.substring(0,5));
  Serial.print("Host name: ");
  Serial.println(info.substring(6,13));
  Serial.print("Kernel release: ");
  Serial.println(info.substring(14,34));
  Serial.print("Kernel version: ");
  Serial.println(info.substring(35,66));
  Serial.print("Hardware: ");
  Serial.println(info.substring(67,71));
  Serial.print("OS: ");
  Serial.println(info.substring(72,81));
  Serial.println("");
  Serial.println("---------------------------------");
  
  delay(5000);
}
