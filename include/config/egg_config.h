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

extern const egg_t chicken_egg; // galinha
extern const egg_t quail_egg; // coderniz
extern const egg_t duck_egg; // pato
extern const egg_t turkey_egg; // peru
extern const egg_t goose_egg; // ganso
extern const egg_t pigeon_egg; // pomba

void print_egg_config(egg_t egg_config);

#endif // !DEBUG
