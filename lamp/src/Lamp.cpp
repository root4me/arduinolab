
#include "Arduino.h"
#include "Lamp.h"

bool isOn();
bool swicthOff();
bool switchOnIfDark();

Lamp::Lamp(int relayPin, bool isActiveLow)
{
        pin=relayPin;
        activeLow = isActiveLow;

        pinMode(pin, OUTPUT);
        switchOff();
}

bool Lamp::switchOn()
{
        if (activeLow)
        {
                digitalWrite(pin, LOW);
        }
        else{
                digitalWrite(pin, LOW);
        }
        switchedOn = true;
}

bool Lamp::switchOff()
{
        if (activeLow)
        {
                digitalWrite(pin, HIGH);
        }
        else
        {
                digitalWrite(pin, LOW);
        }
        switchedOn = false;
}

bool Lamp::isSwitchedOn()
{
        return switchedOn;
}
