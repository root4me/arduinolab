#ifndef _LAMP_h
#define _LAMP_h


class Lamp {
private:
  int pin;
  bool activeLow;

public:
  bool switchOn();
  bool switchOff();
  Lamp(int relayPin, bool isActiveLow);
};

#endif
