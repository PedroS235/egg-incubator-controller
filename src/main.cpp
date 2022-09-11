// #include "config/menus.h"
#include "button_event.h"
#include "config/menus.h"
#include "screen/display.h"
#include <Arduino.h>

// void default_function()
// {
//     Serial.println("Hello world");
// }

Display* display;
Menu* current_menu;
ButtonEvent* btn;

void setup()
{
    // - Giving time to initialize board
    delay(1000);
    Serial.begin(115200);
    display = new Display();
    btn = new ButtonEvent();

    setup_menus();

    display->begin();
    current_menu = &main_menu;
    display->draw_menu(*current_menu);
}

void loop()
{
    int b = btn->getEvent();
    if (b == OK_BTN) {
        current_menu->on_click();
    }
    if (b == UP_BTN) {
        current_menu->move_up();
    }
    if (b == DOWN_BTN) {
        current_menu->move_down();
    }
    display->draw_menu(*current_menu);
}
