#include "button_event.h"
#include "modules/relay.h"
#include "pid_controller.h"
#include "moving_avg_filter.h"
#include "config/configuration.h"
#include "config/egg_config.h"
#include "config/menus.h"
#include "eeprom_manager.h"
#include "modules/buzzer.h"
#include "screen/display.h"
#include <Arduino.h>
#include <DHT.h>
#include <EEPROM.h>
#include <RTClib.h>

// ----------------------------------
// -   Start of Object Instances    -
// ----------------------------------

Display *display;
Menu *current_menu; // NULL = Stats screen
ButtonEvent *btn_event;
DHT dht_sensor(DHT_PIN, DHT_TYPE);
PidController heater_pid(KP, KI, KD);
MovingAvgFilter temp_filter;
MovingAvgFilter humd_filter;
Relay heater(HEATER_PIN);
Relay motor(MOTOR_PIN);
RTC_DS3231 rtc;

// ----------------------------------
// -    End of Object Instances     -
// ----------------------------------

// ----------------------------------
// -   Start of Global Varibales    -
// ----------------------------------

uint8_t curr_state = IDLE_STATE;
egg_t *incubating_egg;
stats_t stats{0.0, 0.0, 0.0, 0.0, 0, 0};

unsigned long motor_timer = 0;

bool start_incubation = false;
bool trigger_motor = false;

float tempTarget = -1.0;
float humdTarget = -1.0;
float current_temp = -1.0;
float current_humd = -1.0;

DateTime end_of_incubation;
DateTime next_motor_rotation;
DateTime stop_motor_rotation;

// ----------------------------------
// -    End of Global Varibales     -
// ----------------------------------

void start_rtc()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }

    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

/**
 * @brief This function reads the temperature and humidity
 * and filters the values based on previous values.
 *
 */
void read_dht_sensor_values()
{
    // Check Temperature
    float temp = dht_sensor.readTemperature();
    if (isnan(temp))
        temp = -1.0;
    current_temp = temp_filter.update(temp);

    // Check Humidity
    float humd = dht_sensor.readHumidity();
    if (isnan(humd))
        humd = -1.0;
    current_humd = humd_filter.update(humd);
}

void setup()
{
    // - Giving time to initialize board
    delay(1000);
    Serial.begin(115200);

    start_rtc();

    // Controller boot
    display = new Display();
    if (!display->begin())
    {
        error_beep();
    }
    display->draw_start_screen();
    start_melody();
    delay(2000);

    btn_event = new ButtonEvent();
    dht_sensor.begin();
    EEPROM.begin(1000);

    read_dht_sensor_values();

    setup_menus();
}

void print_date(DateTime date)
{
    Serial.print(date.day(), DEC);
    Serial.print(':');
    Serial.print(date.hour(), DEC);
    Serial.print(':');
    Serial.print(date.minute(), DEC);
    Serial.print(':');
    Serial.print(date.second(), DEC);
    Serial.println();
}

void routine()
{
    // Check the temperature
    float heater_correction = heater_pid.update(tempTarget, current_temp);
    if (heater_correction >= 0)
    {
        heater.switchOn();
    }
    else
    {
        heater.switchOff();
    }

    // Check the Humidity

    // Check for motor rotation
    DateTime curr_time = rtc.now();
    if (curr_time < stop_motor_rotation)
    {
        if (curr_time == next_motor_rotation)
        {
            // Rotate the motor
            trigger_motor = true;
            motor_timer = millis();
            motor.switchOn();
        }
    }

    if ((millis() - motor_timer > MOTOR_ROTATION_DURATION * 1000) && trigger_motor)
    {
        trigger_motor = false;
        motor.switchOff();
        next_motor_rotation = curr_time + TimeSpan(MOTOR_ROTATION_PERIOD.day(), MOTOR_ROTATION_PERIOD.hour(), MOTOR_ROTATION_PERIOD.minute(), MOTOR_ROTATION_PERIOD.second());
    }

    // Check Days left
    if (curr_time == end_of_incubation)
    {
        curr_state = END_OF_INBUCATION_STATE;
        heater.switchOff();
    }
}

void menu_navigation()
{
    int key_pressed = btn_event->getEvent();
    if (key_pressed == OK_BTN)
    {
        current_menu->on_click();
    }
    if (key_pressed == UP_BTN)
    {
        current_menu->move_up();
    }
    if (key_pressed == DOWN_BTN)
    {
        current_menu->move_down();
    }
}

void update_stats()
{
    stats.temp = current_temp;
    stats.target_temp = tempTarget;
    stats.humd = current_humd;
    stats.target_humd = humdTarget;
    stats.days_left = 15;
    stats.incubation_period = 22;
}

void loop()
{
    update_stats();
    read_dht_sensor_values();

    if (current_menu == NULL)
    {
        display->draw_stats_screen(&stats);
        int key_pressed = btn_event->getEvent();
        if (key_pressed != 0)
            current_menu = &main_menu;
    }
    else
    {
        display->draw_menu(*current_menu);
    }
    menu_navigation();

    if (start_incubation)
    {
        curr_state = IN_INCUBATION_STATE;
        end_of_incubation = rtc.now() + TimeSpan(incubating_egg->incubation_period, 0, 0, 0);
        next_motor_rotation = rtc.now() + TimeSpan(0, 0, 0, 10);
        stop_motor_rotation = rtc.now() + TimeSpan(incubating_egg->incubation_period - incubating_egg->end_motor_rot, 0, 0, 0);
        start_incubation = false;
        print_date(next_motor_rotation);
    }

    if (curr_state == IN_INCUBATION_STATE)
        routine();
}
