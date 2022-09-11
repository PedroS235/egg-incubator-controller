
#include "screen/menu.h"
#include <Arduino.h>
#include <cstdlib>

Menu::Menu(int nbr_of_items)
{
    items = (Item*)malloc(sizeof(Item) * nbr_of_items);
    length = 0;
    selected_index = 0;
}

void Menu::add_item(Item item)
{
    items[length] = item;
    length++;
}

void Menu::on_click()
{
    items[selected_index].click();
}

int Menu::get_menu_lenght() { return length; }

int Menu::get_selected_index() { return selected_index; }

const char* Menu::get_item_name_at(int index)
{
    return items[index].get_item_name();
}

void Menu::set_selected_index(int index)
{
    index >= length || index < 0 ? selected_index : selected_index = index;
}

void Menu::move_down()
{

    if (selected_index < length - 1)
        selected_index++;
}

void Menu::move_up()
{
    if (selected_index >= 1)
        selected_index--;
}

void Menu::print_menu()
{
    for (int i = 0; i < length; i++) {
        selected_index == i ? Serial.print(">") : Serial.print("");
        Serial.println(items[i].get_item_name());
    }
}
