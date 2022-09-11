#ifndef LOG_H
#define LOG_H

#include <Arduino.h>

void print_info(const char* info)
{
    Serial.print("[INFO] - ");
    Serial.println(info);
}

void print_error(const char* error)
{
    Serial.print("[ERROR] - ");
    Serial.println(error);
}

#endif // !LOG_H
