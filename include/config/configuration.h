#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// ----------------------------------
// -              PINS              -
// ----------------------------------

#define BTN_UP_PIN 14   // - Menu up
#define BTN_OK_PIN 27   // - Menu ok
#define BTN_DOWN_PIN 26 // - Menu down

#define HEATER_PIN 19
#define MOTOR_PIN 23
// #define FAN_PIN
// #define SERVO_PIN

// - I2C Pins
#define I2C_SDA_PIN 21
#define I2C_SCK_PIN 22

// - DHT sensor
#define DHT_PIN 32

// - Buzzer
#define BUZZER_PIN 2

// ----------------------------------
// -          SENSOR TYPES          -
// ----------------------------------

#define DHT_TYPE DHT11
// check U8g2 library for your type of screen
#define DISPLAY_TYPE U8G2_SH1106_128X64_NONAME_1_HW_I2C

// ----------------------------------
// -      MOTOR CONFIGURATION       -
// ----------------------------------

// - Motor rotation duration (in seconds)
#define MOTOR_ROTATION_DURATION 7
// - Motor rotation period [year, month, day, hour, minute second]
#define MOTOR_ROTATION_PERIOD DateTime(0, 0, 0, 2, 0, 0)

// ----------------------------------
// -        GUI CONFIGURATION       -
// ----------------------------------

#define SCREEN_SWITCH_PERIOD 5000
#define ROTATE_DISPLAY 1

// ----------------------------------
// -               PID              -
// ----------------------------------

#define KP 0.2 // Proportional value
#define KI 0.1 // Integral value
#define KD 0.1 // Derivative value

// ----------------------------------
// -              STATES            -
// ----------------------------------
#define IDLE_STATE 0
#define IN_INCUBATION_STATE 1
#define END_OF_INBUCATION_STATE 2

#endif // !CONFIGURATION_H
