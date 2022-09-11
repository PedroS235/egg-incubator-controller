#include "screen/item.h"

Item::Item(const char* p_item_name, void (*p_on_click)())
{
    item_name = p_item_name;
    on_click = p_on_click;
}

void Item::click()
{
    (*on_click)();
}

const char* Item::get_item_name()
{
    return item_name;
}
