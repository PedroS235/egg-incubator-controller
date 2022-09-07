#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include <stdint.h>

class Relay {
private:
    uint8_t pin;

public:
    /**
     * @params:
     *  - _pin: pin where the relay is connected
     */
    Relay(uint8_t _pin);

    /**
     * Switches on the current relay
     */
    void switchOn();

    /**
     * Switches off the current relay
     */
    void switchOff();
};

#endif // !RELAY_H
