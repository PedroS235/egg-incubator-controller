#include <moving_avg_filter.h>

MovingAvgFilter::MovingAvgFilter()
{
    for (int i = 0; i < SIZE; i++)
    {
        readings[i] = 0.0;
    }
    index = 0;
}

float MovingAvgFilter::update(float reading)
{
    readings[index] = reading;

    index = (index + 1) % SIZE;

    float sum = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += readings[i];
    }

    return sum / SIZE;
}