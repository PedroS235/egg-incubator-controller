#include "config/menus.h"
#include "screen/display.h"
#include <Arduino.h>

extern Display* display;
extern Menu* current_menu;

Menu main_menu(3);
Menu incubation_menu(7);
Menu settings_menu(7);
Menu incubation_settings_menu(3);
Menu egg_config_menu(7);

void setup_menus()
{
    main_menu.add_item(Item("Start Incubation", main_menu_item1_function));
    main_menu.add_item(Item("Settings", main_menu_item2_function));
    main_menu.add_item(Item("Self Test", main_menu_item3_function));

    incubation_menu.add_item(Item("Go Back", incubation_menu_item1_function));
    incubation_menu.add_item(Item("Chicken Incubation", incubation_menu_item2_function));
    incubation_menu.add_item(Item("Quail Incubation", incubation_menu_item3_function));
    incubation_menu.add_item(Item("Duck Incubation", incubation_menu_item4_function));
    incubation_menu.add_item(Item("Turkey Incubation", incubation_menu_item5_function));
    incubation_menu.add_item(Item("Goose Incubation", incubation_menu_item6_function));
    incubation_menu.add_item(Item("Pigeon Incubation", incubation_menu_item7_function));

    settings_menu.add_item(Item("Go Back", settings_menu_item1_function));
    settings_menu.add_item(Item("Chicken Config", settings_menu_item2_function));
    settings_menu.add_item(Item("Quail Config", settings_menu_item3_function));
    settings_menu.add_item(Item("Duck Config", settings_menu_item4_function));
    settings_menu.add_item(Item("Turkey Config", settings_menu_item5_function));
    settings_menu.add_item(Item("Goose Config", settings_menu_item6_function));
    settings_menu.add_item(Item("Pigeon Config", settings_menu_item7_function));

    incubation_settings_menu.add_item(Item("Go Back", incubation_settings_menu_item1_function));
    incubation_settings_menu.add_item(Item("Target Temperature", incubation_settings_menu_item2_function));
    incubation_settings_menu.add_item(Item("Target Humidity", incubation_settings_menu_item3_function));

    egg_config_menu.add_item(Item("Go Back", egg_config_menu_item1_function));
    egg_config_menu.add_item(Item("Incubation Days", egg_config_menu_item2_function));
    egg_config_menu.add_item(Item("Target Temperature", egg_config_menu_item3_function));
    egg_config_menu.add_item(Item("Target Humidity", egg_config_menu_item4_function));
    egg_config_menu.add_item(Item("Motor Rotation Period", egg_config_menu_item5_function));
    egg_config_menu.add_item(Item("End motor Rotation", egg_config_menu_item6_function));
    egg_config_menu.add_item(Item("Start motor Rotation", egg_config_menu_item7_function));
}

// - main menu functions
void main_menu_item1_function()
{
    display->draw_menu(incubation_menu);
    current_menu = &incubation_menu;
}
void main_menu_item2_function()
{
    display->draw_menu(settings_menu);
    current_menu = &settings_menu;
}
void main_menu_item3_function()
{
    // - start testing and then go back to main menu
}

// - incubation menu functions
void incubation_menu_item1_function()
{
    display->draw_menu(main_menu);
    current_menu = &main_menu;
}
void incubation_menu_item2_function() { }
void incubation_menu_item3_function() { }
void incubation_menu_item4_function() { }
void incubation_menu_item5_function() { }
void incubation_menu_item6_function() { }
void incubation_menu_item7_function() { }

// - settings menu functions
void settings_menu_item1_function()
{
    display->draw_menu(main_menu);
    current_menu = &main_menu;
}
void settings_menu_item2_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void settings_menu_item3_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void settings_menu_item4_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void settings_menu_item5_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void settings_menu_item6_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void settings_menu_item7_function()
{
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}

// - incubation settings menu functions
void incubation_settings_menu_item1_function() { }
void incubation_settings_menu_item2_function() { }
void incubation_settings_menu_item3_function() { }

// - egg config menu functions
void egg_config_menu_item1_function()
{
    display->draw_menu(settings_menu);
    current_menu = &settings_menu;
}
void egg_config_menu_item2_function() { }
void egg_config_menu_item3_function() { }
void egg_config_menu_item4_function() { }
void egg_config_menu_item5_function() { }
void egg_config_menu_item6_function() { }
void egg_config_menu_item7_function() { }
