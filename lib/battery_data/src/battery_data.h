#ifndef BATTERY_DATA_H
#define BATTERY_DATA_H

#include <Arduino.h>
// Analog Pin for battery voltage
#define ANALOG_PIN A0

extern float battery_voltage;

void init_battery_data();

void read_battery_voltage();

#endif