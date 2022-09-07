#include "relay.h"

Relay::Relay(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Relay::switchOn() { digitalWrite(pin, HIGH); }

void Relay::switchOff() { digitalWrite(pin, LOW); }

void Relay::test()
{
    switchOn();
    delay(1000);
    switchOff();
    delay(1000);
    switchOn();
    delay(2000);
    switchOff();
}
