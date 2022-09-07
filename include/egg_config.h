#ifndef EGG_STATS_H
#define EGG_STATS_H

#include <stdint.h>

typedef struct egg {
    uint8_t egg_type;
    uint8_t incubation_period;
    uint8_t rotation_period;
    float temp_target;
    float humd_target;
    uint8_t start_motor_rot;
    uint8_t end_motor_rot;
} egg_t;

#endif // !DEBUG