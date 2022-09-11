#ifndef MENU_H
#define MENU_H

#include "item.h"

class Menu {
private:
    Item* items;
    int selected_index;
    int length;

public:
    Menu(int nbr_of_items);
    void add_item(Item item);
    void on_click();
    int get_selected_index();
    int get_menu_lenght();
    const char* get_item_name_at(int index);
    void print_menu();
    void set_selected_index(int index);
};

#endif // !MENU_H
