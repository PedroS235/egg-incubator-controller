#include "eeprom_manager.h"
#include "config/eeprom_config.h"
#include "config/egg_config.h"
#include <EEPROM.h>

void write_egg_struct(int address, egg_t src)
{
    Serial.print("Writing to address 0x");
    Serial.println(address);
    int curr_address = address;
    EEPROM.writeUChar(curr_address, src.egg_type);
    curr_address += sizeof(char);
    EEPROM.writeUChar(curr_address, src.incubation_period);
    curr_address += sizeof(char);
    EEPROM.writeUChar(curr_address, src.rotation_period);
    curr_address += sizeof(char);
    EEPROM.writeFloat(curr_address, src.temp_target);
    curr_address += sizeof(float);
    EEPROM.writeFloat(curr_address, src.humd_target);
    curr_address += sizeof(float);
    EEPROM.writeUChar(curr_address, src.start_motor_rot);
    curr_address += sizeof(char);
    EEPROM.writeUChar(curr_address, src.end_motor_rot);
    EEPROM.commit();
}

void read_egg_struct(int address, egg_t *dest)
{
    Serial.print("Reading to address 0x");
    Serial.println(address);
    int curr_address = address;
    if (dest != NULL)
    {
        dest->egg_type = EEPROM.readChar(curr_address);
        curr_address += sizeof(char);
        dest->incubation_period = EEPROM.readChar(curr_address);
        curr_address += sizeof(char);
        dest->rotation_period = EEPROM.readChar(curr_address);
        curr_address += sizeof(char);
        dest->temp_target = EEPROM.readFloat(curr_address);
        curr_address += sizeof(float);
        dest->humd_target = EEPROM.readFloat(curr_address);
        curr_address += sizeof(float);
        dest->start_motor_rot = EEPROM.readChar(curr_address);
        curr_address += sizeof(char);
        dest->end_motor_rot = EEPROM.readChar(curr_address);
    }
}

void reset_eeprom()
{
    write_egg_struct(CHICKEN_EGG_CONFIG_ADDR, chicken_egg);
    write_egg_struct(QUAIL_EGG_CONFIG_ADDR, quail_egg);
    write_egg_struct(DUCK_EGG_CONFIG_ADDR, duck_egg);
    write_egg_struct(TURKEY_EGG_CONFIG_ADDR, turkey_egg);
    write_egg_struct(GOOSE_EGG_CONFIG_ADDR, goose_egg);
    write_egg_struct(PIGEON_EGG_CONFIG_ADDR, pigeon_egg);
}
