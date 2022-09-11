// #include "config/menus.h"
#include "config/menus.h"
#include "screen/display.h"
#include <Arduino.h>

// void default_function()
// {
//     Serial.println("Hello world");
// }

Display* display;

void setup()
{
    // - Giving time to initialize board
    delay(1000);
    Serial.begin(115200);
    display = new Display();
    setup_menus();

    // Menu* main_menu = new Menu(3);
    // main_menu->add_item(Item("Start Incubation", default_function));
    // main_menu->add_item(Item("Settings", default_function));
    // main_menu->add_item(Item("Self Test", default_function));

    display->begin();
    display->draw_menu(main_menu);
    delay(1000);
    display->draw_menu(incubation_menu);
    delay(1000);
    display->draw_menu(settings_menu);
    delay(1000);
    display->draw_menu(incubation_settings_menu);
    delay(1000);
    display->draw_menu(egg_config_menu);
}

void loop()
{
    //
}
