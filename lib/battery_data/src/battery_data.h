#ifndef BATTERY_DATA_H
#define BATTERY_DATA_H

#include <Arduino.h>
// Analog Pin for battery voltage
#define ANALOG_PIN A0

const float battery_voltage = 0;

void init_battery_data();

void read_battery_voltage(float battery_voltage);

#endif