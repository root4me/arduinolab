#include "Arduino.h"
#include "TactileSwitch.h"

unsigned long previousVal = LOW;

TactileSwitch s;

void setup()
{

	Serial.begin(9600);
	//pinMode(_pin1,INPUT);
	s.init(2);
	Serial.println("Inside set up");
	pinMode(13, OUTPUT);

}

void loop()
{

	if(s.on())
	{
		Serial.println("On..");
		digitalWrite(13, HIGH);
		//digitalWrite(4, HIGH);
	}
	else
	{
		digitalWrite(13, LOW);
		//digitalWrite(4, LOW);
		Serial.println("Off..");
	}
  delay(200);

}

