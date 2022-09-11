#ifndef MENUS_H
#define MENUS_H

#include "screen/menu.h"
#include <stdint.h>

extern Menu main_menu;
extern Menu incubation_menu;
extern Menu settings_menu;
extern Menu incubation_settings_menu;
extern Menu egg_config_menu;

void default_function();
void setup_menus();
#endif // !MENUS_H
