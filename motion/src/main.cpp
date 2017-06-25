#include "Arduino.h"

#define MOTION_SENSOR_PIN  D2


unsigned long currentMills = 0;
unsigned long motionMills = 0;
// Time in milli seconds for which light will be left on when there is no motion
unsigned long motion_tolerance = 5000;

bool motion()
{
  unsigned long currentVal = digitalRead(MOTION_SENSOR_PIN);

  if(digitalRead(MOTION_SENSOR_PIN) == LOW)
  {
    return false;
  }
  else
  {
    return true;
  }
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(MOTION_SENSOR_PIN, INPUT);
}


void loop()
{

  if (motion())
  {
    // Low swicthes onboard LED to ON
    digitalWrite(LED_BUILTIN, LOW);
    motionMills =  millis();
  }
  else
  {
    currentMills = millis();
    Serial.println(currentMills - motionMills);

    if ((currentMills - motionMills) > motion_tolerance)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      //          Serial.println("shutting off");
      motionMills = 0;
    }

  }

}
