/*
 * SoftwareSerial.h
 * Implementation of SoftwareSerial library for Intel Galileo Gen2 platform
 * - Class definition is derived from SoftwareSerial implementation for AVR
 * - Uses TTYUART class object to access a hardware UART connected to IO2/IO3
 * - Cannot be used with pins other than IO2/IO3, at this time
 *
 * {% copyright %}
 */

#ifndef SoftwareSerial_h
#define SoftwareSerial_h

#include <inttypes.h>
#include <Stream.h>

#include <Arduino.h>
#include <TTYUART.h>

/******************************************************************************
* Definitions
******************************************************************************/

class SoftwareSerial : public Stream
{
private:
  TTYUARTClass & _tty;

  // static data
  static SoftwareSerial *active_object;

public:
  // public methods
  SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false);
  ~SoftwareSerial();
  void begin(long speed);
  bool listen();
  void end();
  bool isListening() { return this == active_object; }
  bool overflow();
  int peek();

  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int available();
  virtual void flush();
  
  using Print::write;
};

#endif /* SoftwareSerial_h */
