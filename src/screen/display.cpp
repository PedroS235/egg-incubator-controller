#include "screen/display.h"
#include "clib/u8g2.h"
#include <math.h>

bool Display::begin(bool rotate_display)
{
    if (!display.begin())
    {
        return false;
    }
    rotate_display ? display.setFlipMode(1) : display.setFlipMode(0);
    display.enableUTF8Print();
    display.setFontPosTop();
    return true;
}

void Display::draw_stats_screen(stats_t *stats)
{
    display.firstPage();
    do
    {
        display.setFont(u8g2_font_7x14B_mf);
        // Temperature
        display.setCursor(0, 0);
        display.print(floor(stats->temp * 10) / 10);
        display.print("/");
        display.print(floor(stats->target_temp * 10) / 10);
        display.println(" °C");

        // Humidity
        display.setCursor(0, display.getMaxCharHeight() + 3);
        display.print(floor(stats->humd * 10) / 10);
        display.print("/");
        display.print(floor(stats->target_humd * 10) / 10);
        display.println(" %");

        // Incubation days
        display.setCursor(0, 2 * display.getMaxCharHeight() + 3);
        display.print(stats->days_left);
        display.print("/");
        display.print(stats->incubation_period);
        display.println(" days");
    } while (display.nextPage());
}

void Display::draw_temperature_screen(float temperature, float target)
{
    display.firstPage();
    do
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
    } while (display.nextPage());
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
    do
    {
        display.setFont(FONT_NAME);
        u8g2_uint_t y_offset = display.getMaxCharHeight();
        int y;

        if (menu.get_selected_index() + 1 > MAX_DEPTH)
        {
            y = -(y_offset) * (1 + menu.get_selected_index() - MAX_DEPTH);
        }
        else
        {
            y = 1;
        }

        for (uint8_t i = 0; i < menu.get_menu_lenght(); i++)
        {
            display.setCursor(0, y + 2);
            if (menu.get_selected_index() == i)
            {
                display.drawLine(0, y, width, y);
                display.drawLine(0, y + y_offset + 1, width, y + y_offset + 1);
            }
            display.println(menu.get_item_name_at(i));
            y += y_offset + 2;
        }
    } while (display.nextPage());
}

void Display::draw_title(const char *title, const uint8_t *font)
{
    display.setFont(font);
    display.setCursor(width / 2 - display.getUTF8Width(title) / 2, 0);
    display.print(title);

    display.drawLine(0, display.getMaxCharHeight() + 2, display.getDisplayWidth(),
                     display.getMaxCharHeight() + 2);
}

void Display::draw_page(const char *title, float value, int change_type)
{
    display.firstPage();
    do
    {
        draw_title(title, FONT_NAME);
        display.setFont(u8g2_font_10x20_mr);
        display.setCursor(0, (height / 2) - (display.getMaxCharHeight() / 2));

        if (change_type == 0)
            display.print("  ");
        else if (change_type == 1)
            display.print(" >");
        else
            display.print(">>");

        display.println(value);
    } while (display.nextPage());
}

void Display::draw_bitmap()
{
    display.firstPage();
    do
    {
        display.drawXBM(0, 0, 16, 16, temperature_bitmap);
        display.drawXBM(50, 50, 16, 16, humidity_bitmap);
    } while (display.nextPage());
}

void Display::draw_incubation_page(float temp, float humd, float tempTarget, float humdTarget)
{
    display.firstPage();
    do
    {
        display.setFont(FONT_NAME);
        display.drawXBM(0, 0, 16, 16, temperature_bitmap);
        display.setCursor(20, 3);
        display.print(temp);
        display.print("/");
        display.print(tempTarget);

        display.drawXBM(0, 20, 16, 16, humidity_bitmap);
        display.setCursor(20, 25);
        display.print(humd);
        display.print("/");
        display.print(humdTarget);
    } while (display.nextPage());
}

void Display::draw_start_screen()
{
    display.firstPage();
    do
    {
        display.drawXBM(width / 2 - 32, height / 2 - 32, 64, 64, egg_bitmap);
    } while (display.nextPage());
}

void Display::draw_error(const char *error_msg)
{

    display.firstPage();
    do
    {
        draw_title("Error", FONT_NAME);
        display.setFont(FONT_NAME);
        display.setCursor(0, height / 2 - display.getMaxCharHeight() / 2);
        display.print(error_msg);
    } while (display.nextPage());
}
