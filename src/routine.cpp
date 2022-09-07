#include "routine.h"
#include "Arduino.h"
#include "HardwareSerial.h"

Routine::Routine(Relay* _heater, Relay* _motor, DHTSensor* _dht,
    egg_stats_t* _egg_stats, RTC_DS3231* _timer)
{
    heater = _heater;
    motor = _motor;
    dht = _dht;
    egg_stats = _egg_stats;
    timer = _timer;
    in_incubation = false;
}

void Routine::start(egg_stats_t* _egg_stats)
{
    if (_egg_stats != NULL) {
        Serial.println("[INFO] - Starting the incubation.");
        DateTime now = timer->now();
        egg_stats = _egg_stats;
        in_incubation = true;
        end_of_incubation_time = now + TimeSpan(egg_stats->incubation_period, 0, 0, 0);
        next_day_time = now + TimeSpan(1, 0, 0, 0);

        motor_timer = 0;
        trigger_motor_rotation = false;
        future_motor_rotation_time = now + TimeSpan(0, MOTOR_ROTATION_PERIOD, 0, 0);
        stop_motor_rotation_time = now + TimeSpan(egg_stats->incubation_period - 2, 0, 0, 0);
    }
}

void Routine::handle_temperature()
{
    float temp = dht->get_temperature();
    if (isnan(temp)) {
        in_incubation = false;
        Serial.println("[ERROR] - No temperature reading - aborting");
    }
    if (temp < egg_stats->temp_target) {
        Serial.println("[INFO] - Temperature inside incubator is lower than the target: ");
        heater->switchOn();
    } else {
        Serial.println("[INFO] - Temperature inside incubator is OK");
        heater->switchOff();
    }
}

void Routine::handle_humidiy()
{
    float humd = dht->get_humidity();
    if (isnan(humd)) {
        in_incubation = false;
        Serial.println("[ERROR] - No temperature reading - aborting");
    }
    if (humd < egg_stats->humd_target - 1) {
        // - code here in case there is smth that raises the humidity
        Serial.print(
            "[INFO] - Humidity inside incubator is lower than the target: ");
        Serial.print(egg_stats->humd_target);
        Serial.println(" %.");
    } else if (humd > egg_stats->humd_target + 1) {
        Serial.print(
            "[INFO] - Humidity inside incubator is higher than the target: ");
        Serial.print(egg_stats->humd_target);
        Serial.println(" %.");
    } else {
        Serial.print("[INFO] - Humidity inside incubator is as expected");
    }
}

void Routine::handle_motor()
{
    DateTime now = timer->now();
    if (now != stop_motor_rotation_time) {
        if (future_motor_rotation_time == now) {
            Serial.println("[INFO] - It's time to rotate the eggs. Turning motor ON");
            trigger_motor_rotation = true;
            future_motor_rotation_time = now + TimeSpan(0, MOTOR_ROTATION_PERIOD, 0, 0);
            motor_timer = millis();
            motor->switchOn();
        }

        if (trigger_motor_rotation) {
            if (millis() - motor_timer >= MOTOR_ROTATION_DURATION * 1000) {
                Serial.println(
                    "[INFO] - Turning motor OFF. Finished rotating the eggs");
                trigger_motor_rotation = false;
                motor->switchOff();
            }
        }
    }
}

void Routine::handle_incubation()
{
    DateTime now = timer->now();
    if (now == end_of_incubation_time) {
        in_incubation = false;
        Serial.println("[INFO] - Starting the incubation.");
    }

    if (now == next_day_time) {
        next_day_time = timer->now() + TimeSpan(1, 0, 0, 0);
        days_left_of_incubation--;
        egg_stats->days_left_of_incubation = days_left_of_incubation;
    }
}

bool Routine::incubation()
{
    if (in_incubation) {
        handle_incubation();
        handle_temperature();
        handle_motor();
        return true;
    }
    Serial.println("Incubation stopped");
    stop();
    return false;
}

void Routine::stop()
{
    motor->switchOff();
    heater->switchOff();
}

uint8_t Routine::get_days_left_of_incubation()
{
    return days_left_of_incubation;
}
