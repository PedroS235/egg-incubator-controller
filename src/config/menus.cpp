#include "config/menus.h"
#include <Arduino.h>

Menu main_menu(3);
Menu incubation_menu(7);
Menu settings_menu(7);
Menu incubation_settings_menu(3);
Menu egg_config_menu(7);

void setup_menus()
{
    main_menu.add_item(Item("Start Incubation", default_function));
    main_menu.add_item(Item("Settings", default_function));
    main_menu.add_item(Item("Self Test", default_function));

    incubation_menu.add_item(Item("Go Back", default_function));
    incubation_menu.add_item(Item("Chicken Incubation", default_function));
    incubation_menu.add_item(Item("Quail Incubation", default_function));
    incubation_menu.add_item(Item("Duck Incubation", default_function));
    incubation_menu.add_item(Item("Turkey Incubation", default_function));
    incubation_menu.add_item(Item("Goose Incubation", default_function));
    incubation_menu.add_item(Item("Pigeon Incubation", default_function));

    settings_menu.add_item(Item("Go Back", default_function));
    settings_menu.add_item(Item("Chicken Config", default_function));
    settings_menu.add_item(Item("Quail Config", default_function));
    settings_menu.add_item(Item("Duck Config", default_function));
    settings_menu.add_item(Item("Turkey Config", default_function));
    settings_menu.add_item(Item("Goose Config", default_function));
    settings_menu.add_item(Item("Pigeon Config", default_function));

    incubation_settings_menu.add_item(Item("Go Back", default_function));
    incubation_settings_menu.add_item(Item("Target Temperature", default_function));
    incubation_settings_menu.add_item(Item("Target Humidity", default_function));

    egg_config_menu.add_item(Item("Go Back", default_function));
    egg_config_menu.add_item(Item("Incubation Days", default_function));
    egg_config_menu.add_item(Item("Target Temperature", default_function));
    egg_config_menu.add_item(Item("Target Humidity", default_function));
    egg_config_menu.add_item(Item("Motor Rotation Period", default_function));
    egg_config_menu.add_item(Item("End motor Rotation", default_function));
    egg_config_menu.add_item(Item("Start motor Rotation", default_function));
}

void default_function()
{
    Serial.println("Hello world");
}
