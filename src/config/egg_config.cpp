#include "config/egg_config.h"
#include <Arduino.h>

const egg_t chicken_egg { 1, 21, 1, 37.7, 55.0, 2, 18 }; // galinha
const egg_t quail_egg { 2, 18, 1, 37.3, 40.0, 2, 15 }; // coderniz
const egg_t duck_egg { 3, 28, 1, 37.5, 55.0, 2, 25 }; // pato
const egg_t turkey_egg { 4, 28, 1, 37.5, 55.0, 2, 25 }; // peru
const egg_t goose_egg { 5, 28, 1, 37.5, 80.0, 2, 25 }; // ganso
const egg_t pigeon_egg { 6, 28, 1, 37.5, 57.0, 2, 15 }; // pomba

void print_egg_config(egg_t egg_config)
{
    Serial.print("Egg type: ");
    Serial.println(egg_config.egg_type);
    Serial.print("Incubation period: ");
    Serial.println(egg_config.incubation_period);
    Serial.print("Rotation Period: ");
    Serial.println(egg_config.rotation_period);
    Serial.print("Temperature target: ");
    Serial.println(egg_config.temp_target);
    Serial.print("Humidity target: ");
    Serial.println(egg_config.humd_target);
    Serial.print("Start of the motor rotation: ");
    Serial.println(egg_config.start_motor_rot);
    Serial.print("End of the motor rotation: ");
    Serial.println(egg_config.end_motor_rot);
}
