#include "display_controller.h"

Display::Display(DHTSensor *_dht, RTC_DS3231 *_timer, bool rotate_display)
{
    display.begin(BTN_OK_PIN, U8X8_PIN_NONE, U8X8_PIN_NONE, BTN_UP_PIN, BTN_DOWN_PIN);
    btn_event = new ButtonEvent(BTN_UP_PIN, BTN_OK_PIN, BTN_DOWN_PIN);
    display.enableUTF8Print();
    display.setFontPosTop();
    if (rotate_display)
        display.setFlipMode(1);
    dht = _dht;
    timer = _timer;
    curr_menu = get_egg_selector_menu();
}

void Display::render(uint8_t screen)
{
    display.firstPage();
    do
    {
        if (screen == 1)
        {
            draw_menu(curr_menu);
        }
        else if (screen == 2)
        {
            incubation_screen();
        }
        draw_curr_time();
    } while (display.nextPage());
    delay(30);
}

void Display::draw_temperature_screen()
{
    float temp = dht->get_temperature();
    float target;
    if (curr_egg_stats == NULL)
    {
        target = -1.0;
    }
    else
    {
        target = curr_egg_stats->temp_target;
    }

    draw_title("Temperatura", u8g2_font_courR10_tr);

    display.setCursor(0, display.getMaxCharHeight() + 5);

    display.setFont(u8g2_font_7x14B_mf);

    if (isnan(temp))
    {
        display.print("Current: ");
        display.print("Error");
        display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
        display.print("Target: ");
        display.print(target);
        display.print(" °C");
    }
    else
    {
        display.print("Current: ");
        display.print(temp);
        display.print(" °C");
        display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
        display.print("Target: ");
        display.print(target);
        display.print(" °C");
    }
}

void Display::draw_humidity_screen()
{
    float humd = dht->get_humidity();
    float target;
    if (curr_egg_stats == NULL)
    {
        target = -1.0;
    }
    else
    {
        target = curr_egg_stats->humd_target;
    }

    draw_title("Humidade", u8g2_font_courR10_tr);

    display.setCursor(0, display.getMaxCharHeight() + 5);

    display.setFont(u8g2_font_7x14B_mf);

    if (isnan(humd))
    {
        display.print("Current: ");
        display.print("Error");
        display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
        display.print("Target: ");
        display.print(target);
        display.print(" %");
    }
    else
    {
        display.print("Current: ");
        display.print(humd);
        display.print(" %");
        display.setCursor(0, display.getCursorY() + display.getMaxCharHeight() + 5);
        display.print("Target: ");
        display.print(target);
        display.print(" %");
    }
}

void Display::draw_menu(menu_t *menu)
{
    draw_title(menu->title, u8g2_font_7x14_mr);
    u8g2_uint_t y = display.getMaxCharHeight() + 5;
    for (int i = 0; i < menu->nbr_items; i++)
    {
        display.setCursor(0, y);
        if (menu->selected == i)
        {
            display.print("> ");
        }
        else
        {
            display.print("  ");
        }
        display.println(menu->items[i]);
        y += display.getMaxCharHeight();
    }
}

void Display::draw_scroll_string(char *string, uint8_t pos_y, uint8_t *font,
                                 bool direction)
{
    display.setFont(font);
    u8g2_uint_t text_width = display.getUTF8Width(string);
    display.drawUTF8(text_scroll_offset, pos_y, string);
    text_scroll_offset--;
    if (text_scroll_offset == -text_width)
        text_scroll_offset = display.getDisplayWidth();
}

void Display::draw_title(char *title, const uint8_t *font)
{

    display.setFont(font);
    display.setCursor(width / 2 - display.getUTF8Width(title) / 2, 0);
    display.print(title);

    display.drawLine(0, display.getMaxCharHeight() + 2, display.getDisplayWidth(),
                     display.getMaxCharHeight() + 2);
}

void Display::draw_stats_screen()
{
    if (curr_egg_stats != NULL)
    {
        draw_title("Estatisticas", u8g2_font_courR10_tr);
        u8g2_uint_t y = display.getMaxCharHeight() + 5;
        display.setFont(u8g2_font_t0_11_mf);
        display.setCursor(0, y);
        display.print("Incubaçao: ");
        display.print(curr_egg_stats->incubation_period);
        y += display.getMaxCharHeight();
        display.setCursor(0, y);
        display.print("Dias restantes: ");
        display.print(curr_egg_stats->days_left_of_incubation);
        y += display.getMaxCharHeight();
        display.setCursor(0, y);
        display.print("Ovo de: ");
        display.print(curr_egg_stats->egg_type);
    }
}

void Display::incubation_screen()
{
    if (millis() - screen_switch_timer >= SCREEN_SWITCH_PERIOD)
    {
        if (curr_screen == 2)
        {
            curr_screen = 0;
        }
        else
        {
            curr_screen++;
        }
        screen_switch_timer += SCREEN_SWITCH_PERIOD;
    }

    switch (curr_screen)
    {
    case 0:
        draw_temperature_screen();
        break;
    case 1:
        draw_humidity_screen();
        break;
    case 2:
        draw_stats_screen();
        break;
    }
}

void Display::draw_curr_time()
{
    DateTime now = timer->now();
    char string_time[10];
    sprintf(string_time, "%d:%d:%d", now.hour(), now.minute(), now.second());
    display.setFont(u8g2_font_t0_11_mf);
    display.setCursor(width / 2 - display.getUTF8Width(string_time) / 2, height - display.getMaxCharHeight());
    display.print(string_time);
}

void Display::set_egg_stats(egg_stats_t *stats)
{
    curr_egg_stats = stats;
}

uint8_t Display::get_menu_selection()
{
    uint8_t event = btn_event->getEvent();
    if (event == UP_BTN)
    {
        move_selected_item_up(curr_menu);
    }
    if (event == OK_BTN)
    {
        return get_selected_item_index(curr_menu);
    }
    if (event == DOWN_BTN)
    {
        move_selected_item_down(curr_menu);
    }
    return -1;
}
