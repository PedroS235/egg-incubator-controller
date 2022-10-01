#include "config/menus.h"
#include "button_event.h"
#include "config/eeprom_config.h"
#include "config/egg_config.h"
#include "eeprom_manager.h"
#include "modules/buzzer.h"
#include "screen/display.h"
#include <Arduino.h>

extern Display* display;
extern Menu* current_menu;
int changing_egg_settings = 0;

Menu main_menu(3);
Menu incubation_menu(7);
Menu settings_menu(3);
Menu egg_config_settings_menu(7);
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
    settings_menu.add_item(Item("Egg Config Settings", settings_menu_item2_function));
    settings_menu.add_item(Item("Load Defaults", settings_menu_item3_function));

    egg_config_settings_menu.add_item(Item("Go Back", egg_config_settings_menu_item1_function));
    egg_config_settings_menu.add_item(Item("Chicken Config", egg_config_settings_menu_item2_function));
    egg_config_settings_menu.add_item(Item("Quail Config", egg_config_settings_menu_item3_function));
    egg_config_settings_menu.add_item(Item("Duck Config", egg_config_settings_menu_item4_function));
    egg_config_settings_menu.add_item(Item("Turkey Config", egg_config_settings_menu_item5_function));
    egg_config_settings_menu.add_item(Item("Goose Config", egg_config_settings_menu_item6_function));
    egg_config_settings_menu.add_item(Item("Pigeon Config", egg_config_settings_menu_item7_function));

    incubation_settings_menu.add_item(Item("Go Back", incubation_settings_menu_item1_function));
    incubation_settings_menu.add_item(Item("Target Temperature", incubation_settings_menu_item2_function));
    incubation_settings_menu.add_item(Item("Target Humidity", incubation_settings_menu_item3_function));

    egg_config_menu.add_item(Item("Go Back", egg_config_menu_item1_function));
    egg_config_menu.add_item(Item("Incubation Days", egg_config_menu_item2_function));
    egg_config_menu.add_item(Item("Target Temperature", egg_config_menu_item3_function));
    egg_config_menu.add_item(Item("Target Humidity", egg_config_menu_item4_function));
    egg_config_menu.add_item(Item("Motor Rotation Period", egg_config_menu_item5_function));
    egg_config_menu.add_item(Item("Start motor Rotation", egg_config_menu_item6_function));
    egg_config_menu.add_item(Item("End motor Rotation", egg_config_menu_item7_function));
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

// - settings menus functions
void settings_menu_item1_function()
{
    display->draw_menu(main_menu);
    current_menu = &main_menu;
}
void settings_menu_item2_function()
{
    display->draw_menu(egg_config_settings_menu);
    current_menu = &egg_config_settings_menu;
}
void settings_menu_item3_function()
{
    reset_eeprom();
}

// - egg settings menu functions
void egg_config_settings_menu_item1_function()
{
    display->draw_menu(settings_menu);
    current_menu = &settings_menu;
}
void egg_config_settings_menu_item2_function()
{
    display->draw_menu(egg_config_menu);
    changing_egg_settings = 1;
    current_menu = &egg_config_menu;
}
void egg_config_settings_menu_item3_function()
{
    changing_egg_settings = 2;
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void egg_config_settings_menu_item4_function()
{
    changing_egg_settings = 3;
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void egg_config_settings_menu_item5_function()
{
    changing_egg_settings = 4;
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void egg_config_settings_menu_item6_function()
{
    changing_egg_settings = 5;
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}
void egg_config_settings_menu_item7_function()
{
    changing_egg_settings = 6;
    display->draw_menu(egg_config_menu);
    current_menu = &egg_config_menu;
}

// - incubation settings menu functions
void incubation_settings_menu_item1_function()
{
    // display->draw_menu(stats);
}
void incubation_settings_menu_item2_function()
{
    extern float Ttarget;
    display->draw_page("Target Temperature", Ttarget, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    bool change_value_small = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big && !change_value_small) {
                change_value_big = true;
            } else if (change_value_big && !change_value_small) {
                change_value_big = false;
                change_value_small = true;
            } else if (!change_value_big && change_value_small) {
                change_value_small = false;
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big && !change_value_small) {
                current_menu = &incubation_settings_menu;
                display->draw_menu(incubation_settings_menu);
                break;
            } else if (change_value_big && !change_value_small) {
                Ttarget++;
            } else if (!change_value_big && change_value_small) {
                Ttarget += 0.1;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big && !change_value_small) {
                Ttarget--;
            } else if (!change_value_big && change_value_small) {
                Ttarget -= 0.1;
            }
        }

        if (change_value_big) {
            display->draw_page("Target Temperature", Ttarget, 1);
        } else if (change_value_small) {
            display->draw_page("Target Temperature", Ttarget, 2);
        } else {
            display->draw_page("Target Temperature", Ttarget, 0);
        }
    }
}

void incubation_settings_menu_item3_function()
{
    extern float Htarget;
    display->draw_page("Target Humidity", Htarget, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    bool change_value_small = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big && !change_value_small) {
                change_value_big = true;
            } else if (change_value_big && !change_value_small) {
                change_value_big = false;
                change_value_small = true;
            } else if (!change_value_big && change_value_small) {
                change_value_small = false;
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big && !change_value_small) {
                current_menu = &incubation_settings_menu;
                display->draw_menu(incubation_settings_menu);
                break;
            } else if (change_value_big && !change_value_small) {
                Htarget++;
            } else if (!change_value_big && change_value_small) {
                Htarget += 0.1;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big && !change_value_small) {
                Htarget--;
            } else if (!change_value_big && change_value_small) {
                Htarget -= 0.1;
            }
        }

        if (change_value_big) {
            display->draw_page("Target Humidity", Htarget, 1);
        } else if (change_value_small) {
            display->draw_page("Target Humidity", Htarget, 2);
        } else {
            display->draw_page("Target Humidity", Htarget, 0);
        }
    }
}

// - egg config menu functions
void egg_config_menu_item1_function()
{
    changing_egg_settings = 0;
    display->draw_menu(egg_config_settings_menu);
    current_menu = &egg_config_settings_menu;
}

void egg_config_menu_item2_function()
{
    uint8_t value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->incubation_period;

    display->draw_page("Incubation Period", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {

            if (!change_value_big) {
                change_value_big = true;
            } else if (change_value_big) {
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big) {
                value++;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big) {
                value--;
            }
        }

        if (change_value_big) {
            display->draw_page("Incubation Days", value, 1);
        } else {
            display->draw_page("Incubation Days", value, 0);
        }
    }

    ptr->incubation_period = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }
    free(ptr);
}

void egg_config_menu_item3_function()
{

    float value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->temp_target;

    display->draw_page("Target Temperature", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    bool change_value_small = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big && !change_value_small) {
                change_value_big = true;
            } else if (change_value_big && !change_value_small) {
                change_value_big = false;
                change_value_small = true;
            } else if (!change_value_big && change_value_small) {
                change_value_small = false;
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big && !change_value_small) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big && !change_value_small) {
                value++;
            } else if (!change_value_big && change_value_small) {
                value += 0.1;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big && !change_value_small) {
                value--;
            } else if (!change_value_big && change_value_small) {
                value -= 0.1;
            }
        }

        if (change_value_big) {
            display->draw_page("Target Temperature", value, 1);
        } else if (change_value_small) {
            display->draw_page("Target Temperature", value, 2);
        } else {
            display->draw_page("Target Temperature", value, 0);
        }
    }

    ptr->temp_target = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }
    free(ptr);
}

void egg_config_menu_item4_function()
{

    float value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->humd_target;

    display->draw_page("Target Humidity", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    bool change_value_small = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big && !change_value_small) {
                change_value_big = true;
            } else if (change_value_big && !change_value_small) {
                change_value_big = false;
                change_value_small = true;
            } else if (!change_value_big && change_value_small) {
                change_value_small = false;
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big && !change_value_small) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big && !change_value_small) {
                value++;
            } else if (!change_value_big && change_value_small) {
                value += 0.1;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big && !change_value_small) {
                value--;
            } else if (!change_value_big && change_value_small) {
                value -= 0.1;
            }
        }

        if (change_value_big) {
            display->draw_page("Target Humidity", value, 1);
        } else if (change_value_small) {
            display->draw_page("Target Humidity", value, 2);
        } else {
            display->draw_page("Target Humidity", value, 0);
        }
    }

    ptr->humd_target = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }
    free(ptr);
}

void egg_config_menu_item5_function()
{
    uint8_t value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->rotation_period;

    display->draw_page("Rotation Period", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big) {
                change_value_big = true;
            } else if (change_value_big) {
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big) {
                value++;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big) {
                value--;
            }
        }

        if (change_value_big) {
            display->draw_page("Rotation Period", value, 1);
        } else {
            display->draw_page("Rotation Period", value, 0);
        }
    }

    ptr->rotation_period = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }
    free(ptr);
}

void egg_config_menu_item6_function()
{
    uint8_t value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->start_motor_rot;

    display->draw_page("Start Rotation", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big) {
                change_value_big = true;
            } else if (change_value_big) {
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big) {
                value++;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big) {
                value--;
            }
        }

        if (change_value_big) {
            display->draw_page("Start Rotation", value, 1);
        } else {
            display->draw_page("Start Rotation", value, 0);
        }
    }

    ptr->start_motor_rot = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }

    free(ptr);
}
void egg_config_menu_item7_function()
{
    uint8_t value;
    egg_t* ptr = (egg_t*)malloc(sizeof(egg_t));

    switch (changing_egg_settings) {
    case 1:
        read_egg_struct(CHICKEN_EGG_CONFIG_ADDR, ptr);
        break;
    case 2:
        read_egg_struct(QUAIL_EGG_CONFIG_ADDR, ptr);
        break;
    case 3:
        read_egg_struct(DUCK_EGG_CONFIG_ADDR, ptr);
        break;
    case 4:
        read_egg_struct(TURKEY_EGG_CONFIG_ADDR, ptr);
        break;
    case 5:
        read_egg_struct(GOOSE_EGG_CONFIG_ADDR, ptr);
        break;
    case 6:
        read_egg_struct(PIGEON_EGG_CONFIG_ADDR, ptr);
        break;
    }

    value = ptr->end_motor_rot;

    display->draw_page("End Rotation", value, 0);
    ButtonEvent* btn_event = new ButtonEvent();
    bool change_value_big = false;
    while (true) {

        int btn_value = btn_event->getEvent();
        if (btn_value == OK_BTN) {
            if (!change_value_big) {
                change_value_big = true;
            } else if (change_value_big) {
                change_value_big = false;
            }
        }
        if (btn_value == UP_BTN) {
            if (!change_value_big) {
                current_menu = &egg_config_menu;
                display->draw_menu(egg_config_menu);
                break;
            } else if (change_value_big) {
                value++;
            }
        }
        if (btn_value == DOWN_BTN) {
            if (change_value_big) {
                value--;
            }
        }

        if (change_value_big) {
            display->draw_page("End Rotation", value, 1);
        } else {
            display->draw_page("End Rotation", value, 0);
        }
    }

    ptr->end_motor_rot = value;

    switch (changing_egg_settings) {
    case 1:
        write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, *ptr);
        break;
    case 2:
        write_egg_struct(QUAIL_EGG_CONFIG_ADDR, *ptr);
        break;
    case 3:
        write_egg_struct(DUCK_EGG_CONFIG_ADDR, *ptr);
        break;
    case 4:
        write_egg_struct(TURKEY_EGG_CONFIG_ADDR, *ptr);
        break;
    case 5:
        write_egg_struct(GOOSE_EGG_CONFIG_ADDR, *ptr);
        break;
    case 6:
        write_egg_struct(PIGEON_EGG_CONFIG_ADDR, *ptr);
        break;
    }

    free(ptr);
}
