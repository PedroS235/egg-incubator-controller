#ifndef MOVING_AVG_FILTER
#define MOVING_AVG_FILTER

#define SIZE 20

class MovingAvgFilter
{
private:
    float readings[SIZE];
    int index;

public:
    /**
     * @brief Construct a new Moving Average Filter object
     *
     */
    MovingAvgFilter();

    /**
     * @brief Computes the filtered reading
     *
     * @param reading: Value to be filtered
     * @return filtered reading.
     */
    float update(float reading);
};

#endif // MOVING_AVG_FILTER