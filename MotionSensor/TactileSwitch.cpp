// 
// 
// 

#include "TactileSwitch.h"
#include <Arduino.h>

int _pin = -1;
bool _enabled = false;
unsigned long _previousVal = LOW;


void TactileSwitch::init(int pin)
{
	pinMode(pin, INPUT);
	_pin = pin;
}

bool TactileSwitch::on()
{

	if (_pin == -1) return false;

	unsigned long currentVal = digitalRead(_pin);
	
	if (currentVal == HIGH) 
	{
		if(_previousVal != currentVal)
		{
			_enabled = !(_enabled);
		}
	}

	_previousVal = currentVal;
	return _enabled;

}



