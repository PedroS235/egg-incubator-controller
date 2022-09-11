#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    void (*on_click)();
    const char* item_name;

public:
    Item(const char* p_item_name, void (*p_on_click)());
    void click();
    const char* get_item_name();
};

#endif // !ITEM_H
