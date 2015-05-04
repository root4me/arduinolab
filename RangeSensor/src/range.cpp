#include "Arduino.h"
#include "TactileSwitch.h"
#include "PingSensor.h"

unsigned long previousVal = LOW;
static int indicattorPin = 13;

TactileSwitch s;
PingSensor p;

void setup()
{
	Serial.begin(9600);
	s.init(2);
	p.init(3);
	Serial.println("Inside set up");
	pinMode(13, OUTPUT);
}

void loop()
{
	if(s.on())
	{
	//	Serial.println("On..");
		digitalWrite(indicattorPin, HIGH);
		if (p.distance() < 6)
		{
			Serial.println("too close ...");
		}

	}
	else
	{
		digitalWrite(indicattorPin, LOW);
	}
	delay(200);
}

