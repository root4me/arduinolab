#include "Arduino.h"
#include "Lamp.h"

// using active low sainsmart 2 channel relay
#define RELAY_1_PIN D3
Lamp floorLamp(RELAY_1_PIN,true);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {

  delay(1000);
  floorLamp.switchOn();
  delay(4000);
  floorLamp.switchOff();

}
