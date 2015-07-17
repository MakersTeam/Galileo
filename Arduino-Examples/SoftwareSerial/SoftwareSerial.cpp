/*
 * {% copyright %}
 */

#include <Arduino.h>
#include <SoftwareSerial_Class.h>
#include <assert.h>

//
// Statics
//
SoftwareSerial *SoftwareSerial::active_object = 0;

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) : 
	_tty(LINUX_SOFTSERIAL_TTY_OBJ)
	// If LINUX_SOFTSERIAL_TTY_OBJ is not defined, SoftwareSerial is unsupported on this platform variant
{
  // This SoftwareSerial implementation supports pins 2/3 only
  assert(receivePin == 2 && transmitPin == 3);

  // This SoftwareSerial implementation supports non-inverted logic only
  assert(!inverse_logic);
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
}

//
// Private methods
//

// This function sets the current object as the "listening"
// one and returns true if it replaces another 
bool SoftwareSerial::listen()
{
  if (active_object != this)
  {
    active_object = this;
    return true;
  }

  return false;
}


//
// Public methods
//

void SoftwareSerial::begin(long speed)
{
  _tty.begin(speed);
  listen();
}

void SoftwareSerial::end()
{
  _tty.end();
}

int SoftwareSerial::read()
{
	if (!isListening())
		return -1;

	return _tty.read();
}

int SoftwareSerial::available()
{
  if (!isListening())
    return 0;

  return _tty.available();
}

size_t SoftwareSerial::write(uint8_t b)
{
  return _tty.write(b);
}

void SoftwareSerial::flush()
{
  if (!isListening())
    return;

  _tty.flush();
}

int SoftwareSerial::peek()
{
  if (!isListening())
    return -1;

  return _tty.peek();
}

bool SoftwareSerial::overflow()
{
  return _tty.overflow();
}
