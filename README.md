# Introduction

This is a simple, smart sensor application for the ESP2866 microchip. The chosen framework is Arduino, with a community package for the ESP2866.

The Dallas DS18B20 temperature sensors are connected to the OneWire bus (check the ModuleConfig.hpp for the OneWire pin selection).

Sensors use the www.asksensors.com server to store data. In this case, the paid account must be required (over the first seven days of the free trial).

It is expected that the device will work as a low-power battery solution (deep sleep).

# To do:
- Enable watchdog.
- Power voltage measurements.
- Enable deep sleep and test the solution.
