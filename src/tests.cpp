#include "tests.h"

bool test_dht_sensor(DHT* dht)
{
    if (isnan(dht->readTemperature()) || isnan(dht->readHumidity()))
        return false;
    return true;
}
