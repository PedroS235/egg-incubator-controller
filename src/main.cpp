#include "button_event.h"
#include "config/configuration.h"
#include "config/egg_config.h"
#include "config/menus.h"
#include "eeprom_manager.h"
#include "modules/buzzer.h"
#include "screen/display.h"
#include <Arduino.h>
#include <DHT.h>
#include <EEPROM.h>

Display* display;
Menu* current_menu;
ButtonEvent* btn_event;
DHT dht_sensor(DHT_PIN, DHT_TYPE);

float Ttarget;
float Htarget;
float TOFFSET = 0;
float HOFFSET = 0;
egg_t* incubating_egg;
bool incubation_started = false;

void setup()
{
    // - Giving time to initialize board
    delay(1000);
    Serial.begin(115200);
    display = new Display();
    if (!display->begin()) {
        error_beep();
    }
    display->draw_start_screen();
    start_melody();
    delay(2000);
    display->draw_error("FAN ERROR");
    delay(2000);

    btn_event = new ButtonEvent();
    dht_sensor.begin();
    EEPROM.begin(1000);

    setup_menus();

    current_menu = &main_menu;
    display->draw_menu(*current_menu);
}

void menu_navigation()
{
    int key_pressed = btn_event->getEvent();
    if (key_pressed == OK_BTN) {
        current_menu->on_click();
    }
    if (key_pressed == UP_BTN) {
        current_menu->move_up();
    }
    if (key_pressed == DOWN_BTN) {
        current_menu->move_down();
    }
}

void loop()
{
    menu_navigation();
    display->draw_menu(*current_menu);
}
