#include "modules/relay.h"

Relay::Relay(uint8_t _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void Relay::switchOn() { digitalWrite(pin, HIGH); }

void Relay::switchOff() { digitalWrite(pin, LOW); }

void Relay::test()
{
    Serial.println("Turning on");
    switchOn();
    delay(1000);
    Serial.println("Turning off");
    switchOff();
    delay(1000);
    Serial.println("Turning on");
    switchOn();
    delay(2000);
    Serial.println("Turning off");
    switchOff();
}
