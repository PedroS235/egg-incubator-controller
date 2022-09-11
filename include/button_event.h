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

class ButtonEvent {
private:
    uint8_t upBtn, okBtn, downBtn;
    unsigned long timer = 0;
    unsigned long interval = 1000;

public:
    /**
     * This class allows to check if a button was pressed.
     * @params:
     *  - upPin: GPIO pin where the up button is connected.
     *  - okPin: GPIO pin where the ok button is connected.
     *  - downPin: GPIO pin where the down button is connected.
     */
    ButtonEvent();

    /**
     * Returns the number of button pressed. If no button is pressed 0 is returned
     */
    int getEvent();
    int getBtn();
};

#endif /* BUTTONEVENT_H */
