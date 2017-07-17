#include "Arduino.h"

//Lite dependent resistor / photocell pin
#define LDR_PIN  A0



void setup()
{
        pinMode(LED_BUILTIN, OUTPUT);
        Serial.begin(9600);
        pinMode(LDR_PIN, INPUT);
}


void loop()
{

        Serial.println(analogRead(A0));
        digitalWrite(LED_BUILTIN, HIGH);
        delay(2000);
        if (analogRead(A0) < 20)
        {
                digitalWrite(LED_BUILTIN, LOW);
        }

}
