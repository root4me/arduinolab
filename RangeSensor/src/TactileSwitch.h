// TactileSwitch.h

#ifndef _TACTILESWITCH_h
#define _TACTILESWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include <Arduino.h>
#endif

class TactileSwitch
{
 private:


 public:
	void init(int pin);
	bool on();
};

extern TactileSwitch TACTILESWITCH;

#endif

