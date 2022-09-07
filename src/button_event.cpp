#include "button_event.h"

ButtonEvent::ButtonEvent(uint8_t upPin, uint8_t okPin, uint8_t downPin)
{
    upBtn = upPin;
    okBtn = okPin;
    downBtn = downPin;
    pinMode(upPin, INPUT);
    pinMode(okPin, INPUT);
    pinMode(downPin, INPUT);
    interval = 200;
}

int ButtonEvent::getEvent()
{
    if (millis() - timer > interval) {
        timer += interval;
        if (digitalRead(upBtn) == HIGH) {
            return UP_BTN;
        } else if (digitalRead(okBtn) == HIGH) {
            return OK_BTN;
        } else if (digitalRead(downBtn) == HIGH) {
            return DOWN_BTN;
        } else {
            return 0;
        }
    }
    return -1;
}
