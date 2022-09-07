#ifndef SENSOR_TESTS_H
#define SENSOR_TESTS_H

#include "DHT.h"
#include <Arduino.h>

bool test_dht_sensor(DHT* dht);
bool test_display();
bool test_rtc();
bool test_relays();

#endif // !SENSOR_TESTS_H
