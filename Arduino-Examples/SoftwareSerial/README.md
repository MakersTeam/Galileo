# SoftwareSerial Library


The SoftwareSerial library is not supported by Galileo; however, there is a workaround that allows using pins 2 and 3 as a serial interface.

The example **SoftwareSerial_GalileoGen2.ino** shows how this workaround works.

#### Things to be considered
* This workaround only work for Galileo Gen2.
* Only the pins 2 and 3 can be used for this purpose.
* The directory *SoftwareSerial_Gen2* contains the files **SoftwareSerial.cpp** and **SoftwareSerial_Class.h**. This directory has to be copied in the Arduino libraries folder.
