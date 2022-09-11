#include "button_event.h"

#include "config/configuration.h"
#include <Arduino.h>

ButtonEvent::ButtonEvent()
{
    pinMode(BTN_UP_PIN, INPUT);
    pinMode(BTN_OK_PIN, INPUT);
    pinMode(BTN_DOWN_PIN, INPUT);
    interval = 200;
}

int ButtonEvent::getEvent()
{
    if (millis() - timer > interval) {
        timer += interval;
        if (digitalRead(BTN_UP_PIN) == HIGH) {
            return UP_BTN;
        } else if (digitalRead(BTN_OK_PIN) == HIGH) {
            return OK_BTN;
        } else if (digitalRead(BTN_DOWN_PIN) == HIGH) {
            return DOWN_BTN;
        }
    }
    return 0;
}
