// ---------------------
// | Start of includes |
// ---------------------

#include <Arduino.h>
#include <RTClib.h>
#include <stdint.h>

//---------------------

#include "button_event.h"
#include "relay.h"

// -------------------
// | End of includes |
// -------------------

// -----------------------------------------------------------------------------------------------------

RTC_DS3231 *timer;
Relay *heater;
Relay *motor;

void timer_setup()
{
    if (!timer->begin())
    {
        if (!timer->begin())
        {
            Serial.println("[ERROR] - Couldn't find RTC");
            Serial.flush();
            while (1)
                delay(10);
        }
    }

    if (timer->lostPower())
    {
        Serial.println("[INFO] - RTC lost power, let's set the time!");
        timer->adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void setup()
{
    // - Giving time to initialize
    delay(2000);

    // - Begining Tests
}

void loop()
{
}
