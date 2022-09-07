#include "gui/menus.h"
#include <stdlib.h>

menu_t* get_egg_selector_menu()
{
    menu_t* egg_selector_menu = (menu_t*)malloc(sizeof(menu_t));
    egg_selector_menu->nbr_items = 2;
    egg_selector_menu->selected = 0;
    egg_selector_menu->title = "Seletor de ovos";
    char** items = (char**)malloc(2 * sizeof(char*));
    items[0] = "Galinha";
    items[1] = "Codorniz";
    egg_selector_menu->items = items;
    return egg_selector_menu;
}

void move_selected_item_up(menu_t* menu)
{
    if (menu->selected > 0)
        menu->selected--;
}
void move_selected_item_down(menu_t* menu)
{
    if (menu->selected < menu->nbr_items - 1)
        menu->selected++;
}
uint8_t get_selected_item_index(menu_t* menu) { return menu->selected; }
