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

    /**
     * @brief Performs a small test by turning on and off the relay!
     * 
     */
    void test();
};

#endif // !RELAY_H
