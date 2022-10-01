#ifndef EEPROM_CONFIG_H
#define EEPROM_CONFIG_H

#define egg_struct_size 65 // bits

#define CHICKEN_EGG_CONFIG_ADDR 100
#define QUAIL_EGG_CONFIG_ADDR (100 + egg_struct_size)
#define DUCK_EGG_CONFIG_ADDR (100 + 2 * egg_struct_size)
#define TURKEY_EGG_CONFIG_ADDR (100 + 3 * egg_struct_size)
#define GOOSE_EGG_CONFIG_ADDR (100 + 4 * egg_struct_size)
#define PIGEON_EGG_CONFIG_ADDR (100 + 5 * egg_struct_size)

#define RESET_TO_DEFAULTS_ADDR 0
#endif // !EEPROM_CONFIG_H
