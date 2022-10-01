#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include "config/egg_config.h"

void write_egg_struct(int address, egg_t egg_config);
void read_egg_struct(int address, egg_t* egg_conig);
void reset_eeprom();

#endif // !EEPROM_MANAGER_H
