#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/*This is the configuration file!
This is the only place that requires changes if any.
In case you have connected the different components to different pins
then update the pin number accordingly
*/

// ----------------------------------
// -           GPIO PINS            -
// ----------------------------------

// GPIO pin for the UP button
#define BTN_UP_PIN 14
// GPIO pin for the OK button
#define BTN_OK_PIN 27
// GPIO pin for the DOWN button
#define BTN_DOWN_PIN 26

// GPIO pin for HEATER relay
#define HEATER_PIN 19
// GPIO pin for MOTOR relay
#define MOTOR_PIN 23
// GPIO pin for FAN
// #define FAN_PIN
// GPIO pin for SERVO
// #define SERVO_PIN

// - I2C GPIO Pins
// These pins should not be changed!
#define I2C_SDA_PIN 21
#define I2C_SCK_PIN 22

// GPIO pin for DHT temperatue/humidity sensor
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
