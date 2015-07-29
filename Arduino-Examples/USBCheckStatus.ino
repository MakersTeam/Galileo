/*
USBCheckStatus.ino - Check the USB Host port status on the Galileo board

This example shows how to check the USB Host port connection status.

This example has been tested on a Galileo Gen2.

This example code is in the public domain.

Revision History
----------------------------------------------------------
    Author		   Date		  Description
----------------------------------------------------------
Diego Villalobos	07-28-2015	Example created

*/

FILE *usb_info_file;
int c, new_usb_status, current_usb_status;
String usb_info;

int checkStatus(){
  /* 
     Create a file in Linux side with the recent activity in the USB bus. Then open that file from the 
     Arduino sketch, read and return the current USB port status. The file created is deleted before
     returning the value read.
  */
  
  String line_output;
  int new_status = 0;
  
  system("dmesg | grep 'USB' | tail -5 > /home/usb_info.txt");
  
  usb_info_file = fopen("/home/usb_info.txt","r");
  
  if (usb_info_file)
  {
    while ((c = getc(usb_info_file)) != EOF) // Keep reading until the end of the file
    {
      if(c != 10) // Detect if it is an end of line
      {
           line_output += (char)c; 
      }
      
      else
      {
        if (line_output.substring(24,38) == "USB disconnect") { new_status = 0; }
        if (line_output.substring(24,49) == "new high-speed USB device") { new_status = 1; }
        line_output = "";
      }
    }
    if (line_output.substring(24,38) == "USB disconnect") { new_status = 0; }
    if (line_output.substring(24,49) == "new high-speed USB device") { new_status = 1; }
    
    fclose(usb_info_file);
   }  
  
  // Delete the file created in the Linux side
  system("rm /home/usb_info.txt");
  
  // Return the status 
  return new_status;
}

void setup() {
  // Initialize the Serial Monitor
  Serial.begin(9600);
  new_usb_status = 0;
  current_usb_status = 0;
}

void loop() {
  
  new_usb_status = checkStatus(); // Return the status of the USB port
  
  // Checks if the status has changed
  if (new_usb_status != current_usb_status){
    current_usb_status = new_usb_status;
    if (current_usb_status == 0) { Serial.println("USB device disconnected"); }
    if (current_usb_status == 1) { Serial.println("USB device connected"); }
  }
  
  delay(1000);
}
