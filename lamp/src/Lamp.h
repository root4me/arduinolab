#ifndef _LAMP_h
#define _LAMP_h


class Lamp {
private:
int pin;
bool activeLow;
bool switchedOn =  false;

public:
bool switchOn();
bool switchOff();
bool isSwitchedOn();
Lamp(int relayPin, bool isActiveLow);
};

#endif
