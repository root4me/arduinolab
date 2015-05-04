/*
 * PingSensor.cpp
 *
 *  Created on: May 3, 2015
 *      Author: harish
 */

#include "PingSensor.h"

#include <Arduino.h>

int pingPin = -1;


void PingSensor::init(int pin)
{
	pinMode(pin, OUTPUT);
	pingPin = pin;
}

long PingSensor::distance()
{
	  long pingTime;
	  long pingTimein;

	  // Activate Ping Sensor. Give a HIGH Pulse for 2 or more micro Seconds
	  pinMode(pingPin, OUTPUT);
	  digitalWrite(pingPin, LOW);
	  delayMicroseconds(2);
	  digitalWrite(pingPin, HIGH);
	  delayMicroseconds(5);
	  digitalWrite(pingPin, LOW);

	  //Receive the ping response
	  pinMode(pingPin,INPUT);
	  pingTime = pulseIn(pingPin, HIGH);

	  // Testing
	  //pingTime= 1000;

	  pingTimein = (pingTime / 73.744) / 2;

	  return pingTimein;

	  // 3000 microseconds ping time is ~20 inches to an obstacle
	  // Refer: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
	  //	Inches = (microseconds / 73.744) / 2
	  //	Centimeters = (microseconds / 29.034) / 2
}
