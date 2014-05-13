
#include "TactileSwitch.h";

TactileSwitch s;

void setup() {
  Serial.begin(9600);
  	s.init(2);
	pinMode(13, OUTPUT);
    //delay(20000);
}

void loop() {
  //Serial.print("IN2 = ");
  //
  //delay(200);
  
  	if(s.on())
	{
		Serial.println("On..");
		digitalWrite(13, HIGH);
		//digitalWrite(4, HIGH);
//motion sensor
                Serial.println(digitalRead(3), DEC);
	}
	else
	{
		digitalWrite(13, LOW);
		//digitalWrite(4, LOW);
		Serial.println("Off..");
	}
  delay(200);
}
