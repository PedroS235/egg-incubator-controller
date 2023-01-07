#include "button_event.h"

#include "config/configuration.h"
#include "modules/buzzer.h"
#include <Arduino.h>

ButtonEvent::ButtonEvent()
{
    pinMode(BTN_UP_PIN, INPUT);
    pinMode(BTN_OK_PIN, INPUT);
    pinMode(BTN_DOWN_PIN, INPUT);
    timer = millis();
}

int ButtonEvent::getEvent()
{
    if (millis() - timer > interval)
    {
        timer = millis();
        if (digitalRead(BTN_UP_PIN) == HIGH)
        {
            button_click_beep();
            return UP_BTN;
        }
        else if (digitalRead(BTN_OK_PIN) == HIGH)
        {
            button_click_beep();
            return OK_BTN;
        }
        else if (digitalRead(BTN_DOWN_PIN) == HIGH)
        {
            button_click_beep();
            return DOWN_BTN;
        }
    }
    return 0;
}
