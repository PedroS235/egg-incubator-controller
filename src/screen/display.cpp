#include "screen/display.h"

bool Display::begin(bool rotate_display)
{
    if (!display.begin()) {
        return false;
    }
    rotate_display ? display.setFlipMode(1) : display.setFlipMode(0);
    display.enableUTF8Print();
    display.setFontPosTop();
    return true;
}

void Display::draw_temperature_screen(float temperature, float target)
{
    draw_title("Temperatura", u8g2_font_courR10_tr);

    display.setCursor(0, display.getMaxCharHeight() + 5);

    display.setFont(u8g2_font_7x14B_mf);
    display.print("Current: ");
    display.print(temperature);
    display.print(" °C");
    display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
    display.print("Target: ");
    display.print(target);
    display.print(" °C");
}

void Display::draw_humidity_screen(float humidity, float target)
{
    draw_title("Humidade", u8g2_font_courR10_tr);

    display.setCursor(0, display.getMaxCharHeight() + 5);

    display.setFont(u8g2_font_7x14B_mf);

    display.print("Current: ");
    display.print(humidity);
    display.print(" %");
    display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
    display.print("Target: ");
    display.print(target);
    display.print(" %");
}

void Display::draw_menu(Menu menu)
{
    display.firstPage();
    do {
        display.setFont(FONT_NAME);
        u8g2_uint_t y_offset = display.getMaxCharHeight();
        int y;

        if (menu.get_selected_index() + 1 > MAX_DEPTH) {
            y = -(y_offset) * (1 + menu.get_selected_index() - MAX_DEPTH);
        } else {
            y = 1;
        }

        for (uint8_t i = 0; i < menu.get_menu_lenght(); i++) {
            display.setCursor(0, y + 2);
            if (menu.get_selected_index() == i) {
                display.drawLine(0, y, width, y);
                display.drawLine(0, y + y_offset + 1, width, y + y_offset + 1);
            }
        }
    } while (display.nextPage());
}

void Display::draw_title(const char* title, const uint8_t* font)
{

    display.firstPage();
    do {
        display.setFont(font);
        display.setCursor(width / 2 - display.getUTF8Width(title) / 2, 0);
        display.print(title);

        display.drawLine(0, display.getMaxCharHeight() + 2, display.getDisplayWidth(),
            display.getMaxCharHeight() + 2);
        //
    } while (display.nextPage());
}
