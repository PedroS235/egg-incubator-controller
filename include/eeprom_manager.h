#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include "config/egg_config.h"

/**
 * @brief Write to eeprom an egg_t struct type.
 *
 * @param address: eeprom accress where to write
 * @param src: data
 */
void write_egg_struct(int address, egg_t src);

/**
 * @brief Read from eeprom an egg_t struct type.
 *
 * @param address: eeprom accress where to read from
 * @param dest: pointer to store the data
 */
void read_egg_struct(int address, egg_t *dest);

/**
 * @brief Write the default values into eeprom.
 *
 */
void reset_eeprom();

#endif // !EEPROM_MANAGER_H
