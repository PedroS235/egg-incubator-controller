# Incubator Controller

## DISCLAIMER

This is a work in progress and thus it has not yet been tested. I do not have currently much time to work on this, why it is moving slowly. I have tested the system for a short period of time and it all seems to be working but no promises on the long run. In case you have any suggestions feel free to mention them to me. In addition, I plan to improve this readme file with all the necessary information, such as the components needed

## Introduction

This is a simple arduino controller designed to controll an incubator. The system is design to work with one oled screen, an heater and a motor.
The controller has a menu where one can choose the different types of eggs that he desires to use, where each egg has its own configuration loaded into eeprom.

## How it works

The controller uses a PID controller in order to control the heater by turning it on/off in order to achieve the desired temperature. In addition, a moving average filter is also begin used in order to filter the temperature readings to account for false readings.

As said, the system support different types of eggs, each with its own configuration. Each egg has an incubation period which when the incubation is started, the system can know when to stop the incubation thanks to the clock module. Thus, whenever the end of incubation is reached the incubation is stopped. In addition, each egg has the period from which the eggs should rotate.

