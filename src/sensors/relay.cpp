#include "sensors/relay.h"

Relay::Relay(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Relay::switchOn() { digitalWrite(pin, HIGH); }

void Relay::switchOff() { digitalWrite(pin, LOW); }
