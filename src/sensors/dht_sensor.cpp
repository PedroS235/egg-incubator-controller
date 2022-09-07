#include "sensors/dht_sensor.h"

DHTSensor::DHTSensor(uint8_t pin, uint8_t type, float _temp_correction,
    float _humd_correction)
{
    dht = new DHT(pin, type);
    dht->begin();
    temp_correction = _temp_correction;
    humd_correction = _humd_correction;
}

float DHTSensor::get_temperature()
{
    return dht->readTemperature() + temp_correction;
}

float DHTSensor::get_humidity()
{
    return dht->readHumidity() + humd_correction;
}
