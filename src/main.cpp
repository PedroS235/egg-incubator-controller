// ---------------------
// | Start of includes |
// ---------------------

#include <Arduino.h>
#include <RTClib.h>
#include <stdint.h>

//---------------------

#include "button_event.h"
#include "gui/display_controller.h"
#include "routine.h"
#include "sensors/relay.h"

// -------------------
// | End of includes |
// -------------------

// -----------------------------------------------------------------------------------------------------

Display *gui;
Routine *routine;
Relay *heater;
Relay *motor;
DHTSensor *dht;

RTC_DS3231 *timer;

egg_stats_t *curr_egg_stats;
unsigned long in_timer = 0;

bool in_menu = true;
uint8_t screen_to_render = 1;

bool in_incubation = false;

void timer_setup() {
  if (!timer->begin()) {
    if (!timer->begin()) {
      Serial.println("[ERROR] - Couldn't find RTC");
      Serial.flush();
      while (1)
        delay(10);
    }
  }

  if (timer->lostPower()) {
    Serial.println("[INFO] - RTC lost power, let's set the time!");
    timer->adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void setup() {
  curr_egg_stats = NULL;
  delay(1000);
  Serial.begin(9600);
  timer = new RTC_DS3231();
  timer_setup();
  heater = new Relay(RELAY_HEATER_PIN);
  motor = new Relay(RELAY_MOTOR_PIN);
  dht = new DHTSensor(DHT_PIN, DHT_TYPE);
  gui = new Display(dht, timer, false);
  routine = new Routine(heater, motor, dht, curr_egg_stats, timer);
}

void loop() {
  if (!routine->incubation()) {
    in_incubation = false;
    curr_egg_stats = NULL;
    in_menu = true;
    screen_to_render = 1;
  }

  if (!in_incubation) {
    if (in_menu) {
      switch (gui->get_menu_selection()) {
      case 0:
        Serial.println("[INFO] - selected chicken");
        curr_egg_stats = get_chicken_egg_stats();
        break;
      case 1:
        Serial.println("[INFO] - selected quail");
        curr_egg_stats = get_quail_egg_stats();
        break;
      default:
        break;
      }
      if (curr_egg_stats != NULL) {
        screen_to_render = 2;
        gui->set_egg_stats(curr_egg_stats);
        routine->start(curr_egg_stats);
        in_menu = false;
      }
    }
  }

  gui->render(screen_to_render);
}
