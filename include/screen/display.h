#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "menu.h"
#include <Arduino.h>
#include <U8g2lib.h>

#ifndef DISPLAY_TYPE
#define DISPLAY_TYPE U8G2_SH1106_128X64_NONAME_1_HW_I2C
#endif // !DISPLAY_TYPE

#define MAX_DEPTH 4
#define FONT_NAME u8g2_font_7x13_mr

class Display {

private:
    DISPLAY_TYPE display = DISPLAY_TYPE(U8G2_R0, U8X8_PIN_NONE);
    u8g2_uint_t width = display.getDisplayWidth();
    u8g2_uint_t height = display.getDisplayHeight();

public:
    bool begin(bool rotate_display = false);
    void draw_temperature_screen(float temperature, float target);
    void draw_humidity_screen(float humdidity, float target);
    void draw_menu(Menu menu);
    void draw_title(const char* title, const uint8_t* font);
};

#endif // !DISPLAY_CONTROLLER_H
