#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

// ---------------------
// | Start of includes |
// ---------------------

#include <stdint.h>

//---------------------

// -------------------
// | End of includes |
// -------------------

#define UP_BTN 1
#define OK_BTN 2
#define DOWN_BTN 3

/**
 * @brief Simple class for a button press event
 *
 * It has an internal timer that prevents a button to be pressed rapidly when
 * pressing the button for long periods of time.
 */
class ButtonEvent
{
private:
    uint8_t upBtn, okBtn, downBtn;
    unsigned long timer = 0;
    unsigned long interval = 250;

public:
    /**
     * Construct a new ButtonEvent object
     */
    ButtonEvent();

    /**
     * @brief This method checks for any button event
     *
     * @return Button pressed. Returns 0 if no button was pressed
     */
    int getEvent();
};

#endif /* BUTTONEVENT_H */
